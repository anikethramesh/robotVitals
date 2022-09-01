#!/usr/bin/env python2

import rospy
from std_msgs.msg import Float64
from sensor_msgs.msg import Imu

class linAcc_roc_maker:
	def __init__(self):
		self.linAcc_roc_pub = rospy.Publisher('/rv_linAcc_z_roc', Float64, queue_size = 10)
		self.linAcc_sub = rospy.Subscriber('/imu/data', Imu, self.linAcc_z_callback)
		self.linAcc_diff_callback = rospy.Timer(rospy.Duration(0.25),self.linAcc_z_timercallback)
		self.number_of_periods = 2
		self.value_list = []

	def linAcc_z_callback(self, msg):
		self.linAcc_z_val = msg.linear_acceleration.z

	def linAcc_z_timercallback(self,event=None):
		output_message = Float64()
		if(len(self.value_list)<self.number_of_periods):
			output_message.data = 0
			self.value_list.append(self.linAcc_z_val)
			# self.message_counter = self.message_counter + 1
		elif(len(self.value_list)==self.number_of_periods):
			self.value_list.pop(0)
			self.value_list.append(self.linAcc_z_val)
			output_message.data = self.value_list[-1] - self.value_list[0]
		self.linAcc_roc_pub.publish(output_message)

rospy.init_node('linAcc_z_roc_maker')
createEvents = linAcc_roc_maker()
rospy.spin()