#!/usr/bin/env python2

import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float64
import math
import numpy as np
import cv2 as cv
from scipy.signal import convolve2d

def estimate_noise(I):

  H, W = I.shape

  M = [[1, -2, 1],
       [-2, 4, -2],
       [1, -2, 1]]

  sigma = np.sum(np.sum(np.absolute(convolve2d(I, M))))
  sigma = sigma * math.sqrt(0.5 * math.pi) / (6 * (W-2) * (H-2))

  return sigma

def callback(msg):
	theta =0
	alpha =0
	beta =0
	x = 0
	y = 0
	width = 600;
	height = 600;
	centerX = width/2;
	centerY = height/2;
	scale = 40;
	blank_image = np.zeros((width,height))
	rate = rospy.Rate(10) # 10hz
	for i in range(len(msg.ranges)):
		theta = msg.angle_min + (i * msg.angle_increment);
		y = scale * msg.ranges[i] * math.cos(theta);
		x = scale * msg.ranges[i] * math.sin(theta);
		y = centerY - y;
		x = centerX - x;
		if(x>0 and x<height and y>0 and y<width):
			blank_image[int(y),int(x)] = 255

	# cv.imshow("Result", blank_image)
	# if cv.waitKey(1) and 0xFF == ord('q'):
	# 	pass

	# print('noise is:', estimate_noise(blank_image))
	pub.publish(estimate_noise(blank_image))


rospy.init_node('scan_values')
pub = rospy.Publisher('/psnr_laserScan', Float64, queue_size=10)
sub = rospy.Subscriber('/scan_with_noise', LaserScan, callback)


rospy.spin()