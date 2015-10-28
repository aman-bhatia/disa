import cv2
import os

pad = 25
name = 1
for f in os.listdir('.'):
	img = cv2.imread(f)
	img = cv2.copyMakeBorder(img,pad,pad,pad,pad,cv2.BORDER_CONSTANT,value = [255,255,255])
	cv2.imwrite(str(name) + '.png',img)
	name += 1