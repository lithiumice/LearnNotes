from airtest.core.api import *
from poco.drivers.android.uiautomation import AndroidUiautomationPoco
import logging
import cv2
from matplotlib import pyplot as plt
from base64 import b64decode
# import io
# import numpy
import time

air_log = logging.getLogger("airtest")
air_log.setLevel('WARNING')
poco = AndroidUiautomationPoco(use_airtest_input=True, screenshot_each_action=False)


def snap():
    content, afix = poco.snapshot()
    return b64decode(content)


def get_sc():
    temp = snap()
    # hash = hashlib.md5(temp).hexdigest()
    with open('temp.jpg', 'wb') as f:
        f.write(temp)
    


#
# img_con = snap()
# buffer = io.BytesIO(img_con)
# img = plt.imread(buffer, 0)


tep_list = ['blue0.jpg', 'red0.jpg', 'brown0.jpg']

touch_list = [[0.2, 0.8], [0.5, 0.8], [0.8, 0.8]]


def is_match(tep_num):
    imgcon = cv2.imread('temp.jpg', 0)
    realImg = imgcon[100:1300,180:540]
    template = cv2.imread(tep_list[tep_num], 0)
    w, h = template.shape[::-1]

    res = cv2.matchTemplate(realImg, template, cv2.TM_CCOEFF)
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
    top_left = max_loc
    bottom_right = (top_left[0] + w, top_left[1] + h)
    cv2.rectangle(realImg, top_left, bottom_right, 255, thickness=2)
    # pos = [top_left[0] + w / 2, top_left[1] + h / 2]

    print(max_val)
    plt.imshow(res, cmap="gray")
    plt.title('Matching Result'), plt.xticks([]), plt.yticks([])
    # plt.subplot(224), plt.imshow(realImg, cmap="gray")
    # plt.title('Detected Point'), plt.xticks([]), plt.yticks([])
    plt.show()
    return max_val


while True:
    get_sc()s
    for i in range(0, 3):
        if is_match(i):
            poco.click(touch_list[i])
        time.sleep(0.6)