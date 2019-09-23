import numpy as np
import cv2
import time
from matplotlib import pyplot as plt

start = time.time()
image = cv2.imread('tt.png')
# if not image:
#     print ('can not open.')
srcWidth, srcHeight, channels = image.shape
crop_x1 = int(srcWidth * 0.15)
crop_y1 = int(srcHeight * 0.25)
crop_x2 = int(srcWidth * 0.8)
crop_y2 = int(srcHeight * 0.75)
crop_image = image[crop_x1: crop_x2, crop_y1: crop_y2]
# cv2.equalizeHist(crop_image,crop_image)
binary = cv2.medianBlur(crop_image, 7)
binary_after = cv2.Canny(binary, 0, 60)
kernel_1 = cv2.getStructuringElement(cv2.MORPH_RECT, (15, 15))
closed = cv2.morphologyEx(binary_after, cv2.MORPH_CLOSE, kernel_1)
closed = cv2.morphologyEx(closed, cv2.MORPH_CLOSE, kernel_1)
kernel_3 = np.ones((3, 3), np.uint8)
erosion = cv2.erode(closed, kernel_3, iterations=3)
# dilation = cv2.dilate(erosion, kernel_3, iterations=3)
# ret, binary = cv2.threshold(binary, 60, 255, cv2.THRESH_BINARY)
# image = cv2.imread("353.jpg")
# gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#
# gradX = cv2.Sobel(gray, ddepth=cv2.cv.CV_32F, dx=1, dy=0, ksize=-1)
# gradY = cv2.Sobel(gray, ddepth=cv2.cv.CV_32F, dx=0, dy=1, ksize=-1)
# gradient = cv2.subtract(gradX, gradY)
# gradient = cv2.convertScaleAbs(gradient)
#
# blurred = cv2.blur(gradient, (9, 9))
# (_, thresh) = cv2.threshold(blurred, 90, 255, cv2.THRESH_BINARY)
#
# kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (25, 25))
# closed = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel)
#
# closed = cv2.erode(closed, None, iterations=4)
# closed = cv2.dilate(closed, None, iterations=4)
_, bin_contours, _ = cv2.findContours(erosion, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
c = sorted(bin_contours, key=cv2.contourArea, reverse=True)[0]
rect = cv2.minAreaRect(c)
box = np.int0(cv2.boxPoints(rect))
cv2.drawContours(crop_image, [box], -1, (0, 255, 0), 3)
plt.imshow(crop_image)
plt.show()
# final = cv2.cvtColor(crop_image, cv2.COLOR_BGR2HSV)
