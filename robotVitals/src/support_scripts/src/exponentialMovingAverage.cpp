//ROS
#include "ros/ros.h"
// #include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

// Binding arguments for callback
#include <boost/bind.hpp>

//general
#include <cmath>
#include <time.h>
#include <vector>
#include <numeric>
#include <string>

class signalProcessor{
	private:
		ros::NodeHandle n_;
		ros::Publisher em_average_pub_;

		ros::Subscriber sub1_;

	//sliding window average variables
	// int slidingWindowSize; 
	std::vector<double> initWindow;
	bool initFlag;
	double x_now, x_prev;

	public:
		signalProcessor(std::string &topicName, int min_periods,double alpha, std::string &topicSuffix){
			initFlag = true;
			// std::cout<<"min periods: "<<min_periods<<"\n";			
			sub1_ = n_.subscribe<std_msgs::Float64>(topicName, 1, boost::bind(&signalProcessor::calculate_exponentialMovingAverage,this,_1,min_periods,alpha));
			em_average_pub_ = n_.advertise<std_msgs::Float64>("/exponentialMovingAverage_"+topicSuffix,1);
			x_now = 0;
			x_prev= 0;
		}		

		void calculate_exponentialMovingAverage(const std_msgs::Float64::ConstPtr& msg, int min_periods, double alpha){
			double newVal = msg->data;
			double sum = 0;
			std_msgs::Float64 em_average_msg_;
			if(initFlag==true){
				// std::cout<<"Gets there\n";
				if(initWindow.size()==min_periods){
					//sum of elements in the vector
					sum = std::accumulate(initWindow.begin(),initWindow.end(),0.0);

					//Publish sliding window average
					x_prev = sum/min_periods;
					// std::cout<<em_average_msg_.data<<"PrintedSOmething\n";
					// em_average_pub_.publish(em_average_msg_);

					// initWindow.erase(initWindow.begin());
					// if(!isnan(newVal))
					// 	initWindow.push_back(newVal);
					initFlag = false;
					// std::cout<<"Gets there three\n";
				}
				else{
					if(std::isfinite(newVal))
						initWindow.push_back(newVal);
					// std::cout<<"initWindow Size: "<<initWindow.size()<<"\n";


				}
			}
			else{
				if(std::isfinite(newVal)){					
					x_now = newVal;
					// std::cout<<"Gets here";
					em_average_msg_.data = (alpha*x_now)+((1-alpha)*x_prev);
					em_average_pub_.publish(em_average_msg_);
					x_prev = em_average_msg_.data;
				}
			}
		}
};

int main(int argc, char *argv[]){
	ros::init(argc, argv, "exponentialMovingAverageCalculator");
	ros::NodeHandle nh("~");
	std::string topicName,topicSuffix;
	int min_periods;
	double alpha;
	nh.getParam("topic", topicName); //Please specify the topic you want to calculate the d/dt for. Im not including type checks so please ensure the datatype always matches.
	nh.getParam("minPeriods", min_periods);// You can regulate the minimum periods here. I go for 16
	nh.getParam("alpha", alpha); // Generally I use 0.6
	nh.getParam("topicSuffix", topicSuffix); // Inevitably people are going to apply the same support scripts to multiple topics. This suffix can differentiate them.
	signalProcessor sp1(topicName,min_periods,alpha,topicSuffix);
	ros::spin();
}