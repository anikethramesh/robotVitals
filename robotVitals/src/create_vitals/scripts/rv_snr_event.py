import rospy
from std_msgs.msg import Float64
import math


class rv_snr:
	def __init__(self):
		self.pub = rospy.Publisher('/rv_snr', Float64, queue_size = 10)
		self.sub = rospy.Subscriber('/psnr_laserScan', Float64, self.callback)
		self.t1 = rospy.getT
	def psnrError_cdf(self, x):
		a = 5
		b = 1
		try:
			p_f = 1/(1 + math.exp(-a*x + a*b))
		except OverflowError:
			p_f = float(0)
			# print('the values that caused this problem is:',x)
		return p_f

	def callback(self,msg):
		self.pub.publish(self.psnrError_cdf(msg.data))

rospy.init_node('snr_vital')
rv = rv_snr()
rospy.spin()