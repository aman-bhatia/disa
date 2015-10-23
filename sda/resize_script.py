import cv2
import os

size = (100,100)

for f in os.listdir('.'):
	if (f.endswith('.png')):
		print(f)
		img = cv2.imread(f)
		img = cv2.resize(img,size)
		cv2.imwrite(f,img)