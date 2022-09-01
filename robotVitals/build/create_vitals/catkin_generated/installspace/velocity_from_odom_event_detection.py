#!/usr/bin/env python2

import rospy
from std_msgs.msg import Float64

class velocity_event_detection:
	
	def __init__(self):
		self.velocity_event_pub = rospy.Publisher('/rv_velocity_event', Float64, queue_size=10)
		self.magROC_sub = rospy.Subscriber('/velocity_odomMag_roc', Float64, self.velocity_event_detection_callback)

		# self.resetCounter = True
		self.zeroVelCounter = 0

	def velocity_event_detection_callback(self, msg):
		output_message = Float64()
		if(msg.data <= 1e-5):
			self.zeroVelCounter = self.zeroVelCounter+1
		else:
			self.zeroVelCounter = 0
		output_message.data = self.zeroVelCounter
		self.velocity_event_pub.publish(output_message)


rospy.init_node('velocity_event_creator')
rv = velocity_event_detection()
rospy.spin()