//ROS
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float64.h"


//OpenCV
#include <opencv2/opencv.hpp>

//general
#include <cmath>

void isExit()
{
	//display or exit program if q is pressed
	char key = cv::waitKey(1);
	if(key == 113)
		exit(0);
}


class SNREstimator{
	private:
		ros::NodeHandle n_;
		ros::Publisher psnr_pub_;
		ros::Subscriber sub1_;
		cv::Mat imScan, prevScan, baseScan;
		int width, height, centreX, centreY, scale;

	public:
		SNREstimator(){
			width = 400;
			height = 600;
			centreX = width/2;
			centreY = height/2;
			scale = 40;

			imScan = cv::Mat::zeros(width, height, CV_8UC1);
			prevScan = cv::Mat::zeros(width, height, CV_8UC1);
			baseScan = cv::Mat::zeros(width, height, CV_8UC1);

			psnr_pub_ = n_.advertise<std_msgs::Float64>("/psnr_laserScan",10);
			sub1_ = n_.subscribe('scan',10, &SNREstimator::get_noiseStats,this);
		}


		void get_noiseStats(const sensor_msgs::LaserScan::ConstPtr & scan){
			std_msgs::Float64 psnr_msg_;
			double psnr;
			// sensor_msgs::LaserScan scanObj = (*scan);
			cv::absdiff(prevScan,imScan,baseScan);
			// baseScan.convertTo(baseScan, CV_32F);
			// baseScan = baseScan.mul()
			
		}
}