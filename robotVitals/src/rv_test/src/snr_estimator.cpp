//ROS
#include<ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64.h>
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
		int width, height, centerX, centerY, scale;

	public:
		SNREstimator(){
			width = 400;
			height = 600;
			centerX = width/2;
			centerY = height/2;
			scale = 40;

			imScan = cv::Mat::zeros(width, height, CV_8UC1);
			prevScan = cv::Mat::zeros(width, height, CV_8UC1);
			baseScan = cv::Mat::zeros(width, height, CV_8UC1);

			psnr_pub_ = n_.advertise<std_msgs::Float64>("/psnr_laserScan",10);
			sub1_ = n_.subscribe<sensor_msgs::LaserScan>("scan_with_noise",10, &SNREstimator::get_noiseStats,this);
		}

		void set_imageFromScan(sensor_msgs::LaserScan scannerObj, bool showImage){
			
			cv::Mat imScan_dupe = cv::Mat::zeros(width,height,CV_8UC1);
			float theta, alpha, beta;
			int y, x;
			// Mat matScan(width, height, CV_8UC1);

			//data acquisition
			if(!scannerObj.ranges.empty()){
				for(int i = 0; i < scannerObj.ranges.size(); i++){
					// std::cout<<"\n SegCheck:"<<scan->ranges[scan->ranges.size()/2];
					// angle_min - start angle of the scan
					// angle_increment - change of angle
					theta = scannerObj.angle_min + (i * scannerObj.angle_increment);
					y = scale * scannerObj.ranges[i] * cos(theta);
					x = scale * scannerObj.ranges[i] * sin(theta);
					y = centerY - y;
					x = centerX - x;

					//fill Mat with data
					if(x>0 && y>0  && x<height && y<width){
						imScan_dupe.at<uchar>(y, x) = 255;
					}
				}
			}
			// else
			// 	{std::cout<<"Empty, program still running";}	
			imScan_dupe.copyTo(imScan);

			// if(showImage){
			// 	// visualizeLaserScan();
			// 	cv::imshow("Scan", imScan_dupe);
			// 	cv::Mat Z = cv::Mat::zeros(imScan_dupe.size(), imScan_dupe.type());
			// 	Z.copyTo(imScan_dupe);
			// 	isExit();
			// }
		// return imScan_dupe;
		}

		void get_noiseStats(const sensor_msgs::LaserScan::ConstPtr& scan){
			std_msgs::Float64 psnr_msg_;
			double psnr;
			sensor_msgs::LaserScan scanObj = (*scan);
			// cv::Mat baseScan;

			//Create image Scan and display it
			set_imageFromScan(scanObj, true);
			cv::absdiff(prevScan,imScan,baseScan);
			baseScan.convertTo(baseScan,CV_32F);

			// cv::imshow("Abs Diff",baseScan);

			baseScan = baseScan.mul(baseScan);
			cv::Scalar s = cv::sum(baseScan);

			double sse = s.val[0] + s.val[1] + s.val[2];
			if(sse <= 1e-10){
				psnr = 0.0;
			}
			else{
				double mse = sse/(prevScan.channels()*prevScan.total());
				psnr = 10.0*log10((255*255)/mse);
			}
			double mse = sse/(prevScan.channels()*prevScan.total());
			psnr = 10.0*log10((255*255)/mse);
			if(isinf(psnr))
				psnr_msg_.data = 0;
			// std::cout<<"\nPeak Signal to noise ratio:"<<psnr;
			else 
				psnr_msg_.data = psnr;

			psnr_pub_.publish(psnr_msg_);
			cv::Mat Z = cv::Mat::zeros(imScan.size(), imScan.type());
			imScan.copyTo(prevScan);
			Z.copyTo(imScan);
		}
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "visualizer");
	ros::NodeHandle n;
	cv::namedWindow("Scan", cv::WINDOW_NORMAL);
	// ros::Publisher 
	// ros::Subscriber sub1 = n.subscribe("scan_final", 100, set_imageFromScan);
	// ros::Subscriber sub2 = n.subscribe("scan_final", 100, get_noiseStats);
	SNREstimator estimator1;
	ros::spin();
	return 0;
}