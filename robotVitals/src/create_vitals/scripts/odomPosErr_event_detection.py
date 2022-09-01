#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64

class odomPosErr_event_detection:
	
	def __init__(self):
		self.odomPosErr_event_pub = rospy.Publisher('/rv_odomPosErr_event', Float64, queue_size=10)
		self.odomPosErrROC_sub = rospy.Subscriber('/odomPosErr_roc', Float64, self.odomPosErr_event_detection_callback)

		# self.resetCounter = True
		self.zeroVelCounter = 0

	def odomPosErr_event_detection_callback(self, msg):
		output_message = Float64()
		if(msg.data >= 0.1):
			self.zeroVelCounter = self.zeroVelCounter+1
		else:
			self.zeroVelCounter = 0
		output_message.data = self.zeroVelCounter
		self.odomPosErr_event_pub.publish(output_message)


rospy.init_node('odomPosErr_event_creator')
rv = odomPosErr_event_detection()
rospy.spin()