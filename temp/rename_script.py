import cv2
import os

name=1
for f in os.listdir('./Furniture'):
	print('./Furniture/' + f)
	img = cv2.imread('./Furniture/' + f)
	cv2.imwrite('./Furniture/' + str(name) + '.png',img)
	name += 1