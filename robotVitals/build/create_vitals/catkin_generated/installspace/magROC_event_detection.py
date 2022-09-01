#!/usr/bin/env python2

import rospy
from std_msgs.msg import Float64

import numpy as np

class magROC_event_detection:
	def __init__(self):
		self.magROC_event_pub = rospy.Publisher('/rv_magROC_event', Float64, queue_size = 10)
		self.magROC_sub = rospy.Subscriber('/magDistFromGoal_roc', Float64, self.magROC_event_detection_callback)

		self.magROC_values = []
		self.corr_vector = np.concatenate((np.linspace(0,-0.5,10), np.linspace(-0.5,0,10)[1:]), axis=None)
		# self.sum = 0
	def magROC_event_detection_callback(self,msg):
		conv_sum = 0
		output_msg = Float64()
		if(len(self.magROC_values)<len(self.corr_vector)):
			self.magROC_values.append(msg.data)
		else:
			data_vector = np.array(self.magROC_values)
			conv_sum = np.convolve(data_vector,self.corr_vector,'valid')
			self.magROC_values.pop(0)
			self.magROC_values.append(msg.data)
		output_msg.data = conv_sum
		self.magROC_event_pub.publish(output_msg)

rospy.init_node('magROC_event_maker')
createEvents = magROC_event_detection()
rospy.spin()


