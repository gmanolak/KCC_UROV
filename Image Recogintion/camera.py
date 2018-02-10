import cv2
import sys
from numpy import array
 
# setup video capture '0' is ID device
cap = cv2.VideoCapture(0)

#get frames store in array
frames = []
#loop keep video open
while True:
	#read each frame ret is success flag, im is the image
	ret,im = cap.read() 
	#show the video
	cv2.imshow('video test',im) 
	frames.append(im)
	#wait respond from the keyboard 
	key = cv2.waitKey(10)
	#esc key
	if key == 27:
		break
#put into an array
frames = array(frames)
	
#check the sizes
print im.shape
print frames.shape
