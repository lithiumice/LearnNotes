import numpy as np
import cv2
from matplotlib import pyplot as plt
from airtest.core.api import *
from base64 import b64decode
import copy
from poco.drivers.android.uiautomation import AndroidUiautomationPoco
poco = AndroidUiautomationPoco(use_airtest_input=True, screenshot_each_action=False)

def get_shot():
    con,ret=poco.snapshot()
    con=b64decode(con)
    with open('tt.jpg','wb') as f:
        f.write(con)

# img = cv2.imread('test.jpg',0)
# fast = cv2.FastFeatureDetector()
# kp = fast.detect(img,None)
# img2 = cv2.drawKeypoints(img, kp, color=(255,0,0))
# plt.imshow(img2)
# plt.show()
# Print all default params
# print "Threshold: ", fast.getInt('threshold')
# print "nonmaxSuppression: ", fast.getBool('nonmaxSuppression')
# print "neighborhood: ", fast.getInt('type')
# print "Total Keypoints with nonmaxSuppression: ", len(kp)
def showi(f):
    plt.imshow(f)
    plt.show()

red=(90,90,250)
blue=(170,150,50)
yellow=(123,175,216)
image = cv2.imread('tt.png')
if not image:
    print ('can not open.')
image_bak=copy.deepcopy(image)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
srcWidth, srcHeight, channels = image.shape
crop_x1 = int(srcWidth * 0.15)
crop_y1 = int(srcHeight * 0.25)
crop_x2 = int(srcWidth * 0.8)
crop_y2 = int(srcHeight * 0.75)
crop_image = gray[crop_x1: crop_x2, crop_y1: crop_y2]
showi(crop_image)
binary = cv2.medianBlur(crop_image, 7)
ret, binary = cv2.threshold(binary, 60, 255, cv2.THRESH_BINARY)

kernel_3 = np.ones((3, 3), np.uint8)
dilation = cv2.dilate(binary, kernel_3, iterations=1)
dilation = cv2.dilate(dilation, kernel_3, iterations=1)
erosion = cv2.erode(dilation, kernel_3, iterations=1)
erosion = cv2.erode(erosion, kernel_3, iterations=1)

binary_after = cv2.Canny(erosion, 0, 60)
_, bin_contours, _ = cv2.findContours(binary_after, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(image_bak,bin_contours,-1,color=(255,0,0))

HSV = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
# for idx,c in enumerate(contours):
#     if len(c) < 10:

#         continue
#     epsilon = 233
#     while True:
#         approx = cv2.approxPolyDP(c,epsilon,True)
#         print("idx,epsilon,len(approx),len(c)=%d,%d,%d,%d"%(idx,epsilon,len(approx),len(c)))
#         if (len(approx) < 4):
#             break
#         if math.fabs(cv2.contourArea(approx)) > Config.min_area:
#             if (len(approx) > 4):
#                 epsilon += Config.epsilon_step
#                 print("epsilon=%d, count=%d"%(epsilon,len(approx)))
#                 continue
#             else:
#                 for p in approx:
#                     cv2.circle(binary,(p[0][0],p[0][1]),8,(255,255,0),thickness=-1)
#                     approx = approx.reshape((4, 2))
#                    [top-left, top-right, bottom-right, bottom-left]
#                     src_rect = order_points(approx)
#                 cv2.drawContours(image, c, -1, (0,255,255),1)
#                 cv2.line(image, (src_rect[0][0],src_rect[0][1]),(src_rect[1][0],src_rect[1][1]),color=(100,255,100))
#                 cv2.line(image, (src_rect[2][0],src_rect[2][1]),(src_rect[1][0],src_rect[1][1]),color=(100,255,100))
#                 cv2.line(image, (src_rect[2][0],src_rect[2][1]),(src_rect[3][0],src_rect[3][1]),color=(100,255,100))
#                 cv2.line(image, (src_rect[0][0],src_rect[0][1]),(src_rect[3][0],src_rect[3][1]),color=(100,255,100)) # 获取最小矩形包络
#                 rect = cv2.minAreaRect(approx)
#                 rect = cv2.maxAreaRect(approx)
#                 box = cv2.boxPoints(rect)
#                 box = np.int0(box)
#                 box = box.reshape(4,2)
#                 box = order_points(box)
#                 print("approx->box")
#                 print(approx)
#                 print(src_rect)
#                 print(box)
#                 w,h = point_distance(box[0],box[1]), \
#                       point_distance(box[1],box[2]) print("w,h=%d,%d"%(w,h))
