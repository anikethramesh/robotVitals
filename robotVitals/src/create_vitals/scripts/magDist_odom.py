#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Odometry

class magDistOdom_maker:
	def __init__(self):
		self.magDist_pub = rospy.Publisher('/magDistFromGoal', Float64, queue_size = 10)
		self.odomPosErr_pub = rospy.Publisher('/odomPosErr', Float64, queue_size = 10)
		self.odomMag_pub = rospy.Publisher('/odomMag', Float64, queue_size=10)
		self.movebase_sub = rospy.Subscriber('/move_base/current_goal', PoseStamped, self.movebase_callback)
		self.odom_sub = rospy.Subscriber('/odometry/filtered', Odometry, self.odom_callback)
		self.huskyOdom_sub = rospy.Subscriber('/husky_velocity_controller/odom', Odometry, self.huskyOdom_callback)
		self.odomPosErrRoc_callback = rospy.Timer(rospy.Duration(0.33), self.odomPosErr_callback)
		self.magDistRoc_callback = rospy.Timer(rospy.Duration(0.33), self.magDist_callback)

		self.goalSet = False

	def movebase_callback(self,msg):
		self.goalSet = True
		self.currentGoal = msg.pose.position

	def odom_callback(self,msg):
		self.odomFilteredPosition = msg.pose.pose.position

	def huskyOdom_callback(self,msg):
		self.huskyOdomPosition = msg.pose.pose.position

	def magDist_callback(self,event=None):
		if(self.goalSet):
			msg = Float64()
			x = self.currentGoal.x - self.odomFilteredPosition.x
			y = self.currentGoal.y - self.odomFilteredPosition.y
			z = self.currentGoal.z - self.odomFilteredPosition.z
			msg.data = (x**2 + y**2 + z**2)**0.5
			self.magDist_pub.publish(msg)

	def odomPosErr_callback(self, event=None):
		msg = Float64()
		x = self.huskyOdomPosition.x - self.odomFilteredPosition.x
		y = self.huskyOdomPosition.y - self.odomFilteredPosition.y
		z = self.huskyOdomPosition.z - self.odomFilteredPosition.z		
		msg.data = (x**2 + y**2 + z**2)**0.5

		# print("Look here mofos", msg.data)
		self.odomPosErr_pub.publish(msg)

		odomMagMsg = Float64()
		odomMagMsg.data = ((self.odomFilteredPosition.x*2) + (self.odomFilteredPosition.y*2) + (self.odomFilteredPosition.z*2))**0.5
		self.odomMag_pub.publish(odomMagMsg)

rospy.init_node('magDist_odom_maker')
createEvents = magDistOdom_maker()
rospy.spin()