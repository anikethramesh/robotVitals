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
		ros::Publisher dxdt_pub_;

		ros::Subscriber sub1_;
		//For calcualating derivative
		double current_time, old_time;
		double current_val, old_val;
		// double time_threshold; // The smallest dt value allowed

	public:
		signalProcessor(std::string &topicName, double time_threshold, std::string &topicSuffix){
			old_time = 0;
			current_time = 0;
			old_val = 0;
			current_val = 0;
			// time_threshold = 0.9;

			sub1_ = n_.subscribe<std_msgs::Float64>(topicName, 1, boost::bind(&signalProcessor::calculate_derivative,this,_1,time_threshold));
			dxdt_pub_ = n_.advertise<std_msgs::Float64>("/dxdt_"+topicSuffix,1);
		}

		void calculate_derivative(const std_msgs::Float64::ConstPtr& msg, double time_threshold){
		std_msgs::Float64 dxdt_msg_;
		current_val = msg->data;
		current_time = ros::Time::now().toSec();

		double derivative = 0;
			//Time Threshold can be close to 1 second if you dont want to see differential errors below 1 second. The lower this value is, higher the volatility of d/dt.
			if((current_time - old_time) >time_threshold){
				derivative = (current_val - old_val)/(current_time - old_time);
				old_time = current_time;
				old_val = current_val;
			}
			dxdt_msg_.data = derivative;
			dxdt_pub_.publish(dxdt_msg_);			
		}

};

int main(int argc, char *argv[]){
	ros::init(argc, argv, "derivativeCalculator");
	ros::NodeHandle nh("~");
	std::string topicName,topicSuffix;
	float dt_minVal;

	nh.getParam("topic", topicName); //Please specify the topic you want to calculate the d/dt for. Im not including type checks so please ensure the datatype always matches.
	nh.getParam("dt_minVal", dt_minVal);// You can regulate the minimum value of dt here. I usually go for 0.8 to 1 (seconds)
	nh.getParam("topicSuffix", topicSuffix); // Inevitably people are going to apply the same support scripts to multiple topics. This suffix can differentiate them.
	// std::cout<<topicName;
	signalProcessor sp1(topicName, dt_minVal,topicSuffix);
	ros::spin();

}