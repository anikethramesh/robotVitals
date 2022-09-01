#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64

class magDistOdom_roc_maker:

	def __init__(self):
		self.magDist_odom_roc_pub = rospy.Publisher('/magDistFromGoal_roc', Float64, queue_size=10)

		self.magDist_odom_sub = rospy.Subscriber('/magDistFromGoal', Float64, self.magDist_odom_roc_callback)

		self.value_list = []
		# self.message_counter = 0
		self.number_of_periods = 3		

	def magDist_odom_roc_callback(self,msg):
		output_message = Float64()
		if(len(self.value_list)<self.number_of_periods):
			output_message.data = 0
			self.value_list.append(msg.data)
			# self.message_counter = self.message_counter + 1
		elif(len(self.value_list)==self.number_of_periods):
			self.value_list.pop(0)
			self.value_list.append(msg.data)
			output_message.data = self.value_list[-1] - self.value_list[0]
		self.magDist_odom_roc_pub.publish(output_message)
		# print(self.value_list)

rospy.init_node('magDistFromGoal_differentiator')
rv = magDistOdom_roc_maker()
rospy.spin()
		
	# 	self.prev_val = 0
	# 	self.curr_val = 0
	# 	self.message_counter = 0
	# 	self.number_of_periods = 3
	# 	self.first_time = True

	# def magDist_odom_roc_callback(self,msg):
	# 	self.curr_val = msg.data

	# 	if(self.first_time):
	# 		self.prev_val = msg.data
	# 		self.first_time = False

	# 	self.message_counter = self.message_counter + 1
	# 	if(message_counter == self.number_of_periods):
	# 		diff = self.curr_val - self.prev_val
	# 		self.prev_val = self.curr_val
	# 		self.message_counter = 0
	# 	else:
	# 		diff = 0