//ROS
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

//OpenCV
#include <opencv2/opencv.hpp>

//general
#include <cmath>

using namespace std;
using namespace cv;

//global
const int width = 400;
const int height = 600;
const int centerX = width/2;
const int centerY = height/2;
int scale = 40;

void isExit(){
	//display or exit program if q is pressed
	char key = waitKey(1);
	if(key == 113)
		exit(0);
}

void visualizeLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
	float theta, alpha, beta;
	int y, x;
	cv::Mat matScan = cv::Mat::zeros(width, height, CV_8UC1);

	//data acquisition
	for(int i = 0; i<scan->ranges.size(); i++){
		// angle_min - start angle of the scan
		// angle_increment - change of angle
		theta = scan->angle_min + (i * scan->angle_increment);
		y = scale * scan->ranges[i] * cos(theta);
		x = scale * scan->ranges[i] * sin(theta);
		y = centerY - y;
		x = centerX - x;

		//fill Mat with data
		if(x>0 && x<height && y>0 && y<width)
		{
			matScan.at<unsigned char>(y, x) = 255;
		}
	}
	//visualize
	imshow("Scan", matScan);
	//fill matScan with zeros
	Mat Z = Mat::zeros(matScan.size(), matScan.type());
	Z.copyTo(matScan);
	isExit();
}



int main(int argc, char **argv){
	ros::init(argc, argv, "visualizer");
	ros::NodeHandle n;
	namedWindow("Scan", WINDOW_NORMAL);
	ros::Subscriber sub = n.subscribe("scan", 100, visualizeLaserScan);
	ros::spin();
	return 0;
}