#!/usr/bin/env python2

import rospy
from std_msgs.msg import Float64

class odomPosErr_roc_maker:

	def __init__(self):
		self.odomPosErr_roc_pub = rospy.Publisher('/odomPosErr_roc', Float64, queue_size=10)

		self.odomPosErr_sub = rospy.Subscriber('/odomPosErr', Float64, self.odomPosErr_roc_callback)

		self.value_list = []
		# self.message_counter = 0
		self.number_of_periods = 2	

	def odomPosErr_roc_callback(self,msg):
		output_message = Float64()
		if(len(self.value_list)<self.number_of_periods):
			output_message.data = 0
			self.value_list.append(msg.data)
			# self.message_counter = self.message_counter + 1
		elif(len(self.value_list)==self.number_of_periods):
			self.value_list.pop(0)
			self.value_list.append(msg.data)
			output_message.data = self.value_list[-1] - self.value_list[0]
		self.odomPosErr_roc_pub.publish(output_message)
		# print(self.value_list)

rospy.init_node('odomPosErr_differentiator')
rv = odomPosErr_roc_maker()
rospy.spin()