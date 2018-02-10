import numpy as np
import cv2
from matplotlib import pyplot as plt

MIN_MATCH_COUNT = 10

img1 = cv2.imread('/Users/nguyenbanh/Downloads/StopSign.jpg',0) # queryImage
img2 = cv2.imread('/Users/nguyenbanh/Downloads/parkinglot.jpg',0) # trainImage 

# Initiate SIFT detector
sift = cv2.xfeatures2d.SIFT_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = sift.detectAndCompute(img1,None) 
kp2, des2 = sift.detectAndCompute(img2,None)

#FLANN based Matcher
#stands for Fast Library for Approximate Nearest Neighbors
#two dictionaries which specifies the algorithm to be used, its related parameters for FLANN based matcher
FLANN_INDEX_KDTREE = 0
#decide what algorithm use for SIFT we can use FLANN_INDEX_KDTREE
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
#the number of times the trees in the index should be recursively traversed, higher value better precision
search_params = dict(checks = 1000)

#FLANN based matcher 
flann = cv2.FlannBasedMatcher(index_params, search_params)

matches = flann.knnMatch(des1,des2,k=2)

# store all the good matches as per Lowe's ratio test.
good = []
for m,n in matches:
	if m.distance < 0.7*n.distance: 
		good.append(m)

#make the set of good points from both the images
if len(good)>MIN_MATCH_COUNT:
	#source points
	src_pts = np.float32([ kp1[m.queryIdx].pt for m in good ]).reshape(-1,1,2)
	#destination points
	dst_pts = np.float32([ kp2[m.trainIdx].pt for m in good ]).reshape(-1,1,2)
	
	#function from calib3d module
	#find the perpective transformation of that object
	M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
	#returns a mask which specifies the inlier and outlier points
	matchesMask = mask.ravel().tolist()
	
	h,w = img1.shape
	pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
	#find the object
	dst = cv2.perspectiveTransform(pts,M)
    #draw the line around the Object marked in white color 
	img2 = cv2.polylines(img2,[np.int32(dst)],True,255,3, cv2.LINE_AA)
else:
	print "Not enough matches are found - %d/%d" % (len(good),MIN_MATCH_COUNT)
	matchesMask = None

# draw matches in green color
draw_params = dict(matchColor = (0,255,0), singlePointColor = None,matchesMask = matchesMask, flags = 2)

img3 = cv2.drawMatches(img1,kp1,img2,kp2,good,None,**draw_params) 

plt.imshow(img3, 'gray'),plt.show()
 
