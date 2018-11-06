import cv2
import numpy as np
import os
import glob

pathorig = './empty/orig'
pathsave = './empty'
i = 0
#'./empty/orig/empty.jpg'
for filename in glob.glob('./empty/orig/*.jpg'):
	img = cv2.imread(filename)
	h,w = img.shape[:2]
	cw = int(w/2)
	ch = int(h/2)
	c = (int(w/2),int(h/2))
	
	#cropped
	crop1 = img[0:ch, 0:cw]
	crop2 = img[0:ch, cw:w]
	crop3 = img[ch:h, 0:cw]
	crop4 = img[ch:h, cw:w]
	cv2.imwrite('./empty/test'+str(i)+'0.jpg', crop1)
	cv2.imwrite('./empty/test'+str(i)+'1.jpg', crop2)
	cv2.imwrite('./empty/test'+str(i)+'2.jpg', crop3)
	cv2.imwrite('./empty/test'+str(i)+'3.jpg', crop4)
	
	i+=1


i=0
for filename in glob.glob('./empty/*.jpg'):
	img = cv2.imread(filename)
	h,w = img.shape[:2]
	cw = int(w/2)
	ch = int(h/2)
	c = (h/2,w/2)
	M = cv2.getRotationMatrix2D(c,90,1.0)
	
	#rotated
	r1 = cv2.warpAffine(img,M,(h,w))
	# r2 = cv2.warpAffine(r1,M,(w,h))
	# r3 = cv2.warpAffine(r2,M,(h,w))
	# r4 = cv2.warpAffine(r3,M,(w,h))
	cv2.imwrite('./empty/rotated/rot'+str(i)+'-0.jpg',r1)
	# cv2.imwrite('./empty/rotated/rot'+str(i)+'-1.jpg',r2)
	# cv2.imwrite('./empty/rotated/rot'+str(i)+'-2.jpg',r3)
	# cv2.imwrite('./empty/rotated/rot'+str(i)+'-3.jpg',r4)
	
	i+=1
	

#cv2.imshow('image',img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()
#gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

#crop1 = img[0:int(h/2), 0:int(w/2)]
#crop2 = img[0:int(h/2), int(w/2):w]
#crop3 = img[int(h/2):h, 0:int(w/2)]
#crop4 = img[int(h/2):h, int(w/2):w]

#if the image is > 100x100 save it