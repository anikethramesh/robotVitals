#!/usr/bin/env python2

import rospy
from std_msgs.msg import Float64
import math

class sufferingClass:

	def __init__(self):
		self.rv_magROC_ProbSuff_pub = rospy.Publisher('/probSuffering_rv_magROC', Float64, queue_size = 10)
		self.rv_velocityEvent_ProbSuff_pub = rospy.Publisher('/probSuffering_rv_velocityEvent', Float64, queue_size = 10)
		self.rv_odomPosErrEvent_ProbSuff_pub = rospy.Publisher('/probSuffering_rv_odomPosErrEvent', Float64, queue_size = 10)
		self.rv_linAccROC_ProbSuff_pub = rospy.Publisher('/probSuffering_rv_linAccROC', Float64, queue_size = 10)
		self.rv_snr_ProbSuff_pub = rospy.Publisher('/probSuffering_rv_snr', Float64, queue_size = 10)

		# self.probSuff_total_pub = rospy.Publisher('/probSuffering_total', Float64, queue_size=10)

		self.rv_magROC_sub = rospy.Subscriber('/rv_magROC_event', Float64, self.rv2ps_magroc_callback)
		self.rv_velocityEvent_sub = rospy.Subscriber('/rv_velocity_event', Float64, self.rv2ps_velocityEvent_callback)
		self.rv_odomPosErrEvent_sub = rospy.Subscriber('/rv_odomPosErr_event', Float64, self.rv2ps_odomPosErrEvent_callback)
		self.rv_linAccZROC_sub = rospy.Subscriber('/rv_linAcc_z_roc', Float64, self.rv2ps_linAccZROC_callback)
		self.rv_snr_laserScan_sub = rospy.Subscriber('/psnr_laserScan', Float64, self.rv2ps_psnr_callback)

	def rv2ps_magroc_callback(self,msg):
		probSuff = Float64()
		a = -6
		b = 0.18
		try:
			probSuff.data = 1/(1 + math.exp(-a*msg.data + a*b))
		except OverflowError:
			probSuff.data
		self.rv_magROC_ProbSuff_pub.publish(probSuff)

	def rv2ps_velocityEvent_callback(self,msg):
		probSuff = Float64()
		a = 1.5
		b = 2.5
		try:
			probSuff.data = 1/(1 + math.exp(-a*msg.data + a*b))
		except OverflowError:
			probSuff.data = float(0)
		self.rv_magROC_ProbSuff_pub.publish(probSuff)

	def rv2ps_odomPosErrEvent_callback(self,msg):
		probSuff = Float64()
		k = 0.2
		buff = k*msg.data
		if(buff>1):
			probSuff.data = 1
		elif(buff<0):
			probSuff.data = 0
		else:
			probSuff.data = buff
		self.rv_odomPosErrEvent_ProbSuff_pub.publish(probSuff)

	def rv2ps_linAccZROC_callback(self,msg):
		probSuff = Float64()
		sigma1 = 0.4
		sigma2 = -0.9
		mu = 0
		output = 1 - (1/(math.sqrt(2*math.pi)*sigma1))*(math.exp( - math.pow(msg.data - mu,2)/(2*math.pow(sigma2,2))))
		if(output>1):
			probSuff.data = 1
		elif(output<0):
			probSuff.data = 0
		else:
			probSuff.data = output
		self.rv_linAccROC_ProbSuff_pub.publish(probSuff)

	def rv2ps_psnr_callback(self,msg):
		probSuff = Float64()
		a = 5
		b = 1
		try:
			probSuff.data = 1/(1 + math.exp(-a*msg.data + a*b))
		except OverflowError:
			probSuff.data = float(0)
			# print('the values that caused this problem is:',x)
		self.rv_snr_ProbSuff_pub.publish(probSuff)


rospy.init_node('ProbabilityOfSuffering')
createEvents = sufferingClass()
rospy.spin()