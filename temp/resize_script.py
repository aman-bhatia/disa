import cv2
import os

size = (500,500)

for folder in os.listdir('./original'):
	for f in os.listdir('./original/' + folder):
		if (f.endswith('.png')):
			print('./original/' + folder + '/' + f)
			img = cv2.imread('./original/' + folder + '/' + f)
			cv2.threshold(img,100,255,cv2.THRESH_BINARY,img)			
			img = cv2.resize(img,size,img,0,0,cv2.INTER_AREA)
			cv2.imwrite('./compressed/' + folder + '/' + f,img)