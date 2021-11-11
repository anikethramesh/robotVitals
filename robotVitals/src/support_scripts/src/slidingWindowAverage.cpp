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
		ros::Publisher sw_average_pub_;

		ros::Subscriber sub1_;

	//sliding window average variables
	// int slidingWindowSize; 
	std::vector<double> slidingWindowValues;

	public:
		signalProcessor(std::string &topicName, int windowSize, std::string &topicSuffix){
			sub1_ = n_.subscribe<std_msgs::Float64>(topicName, 1, boost::bind(&signalProcessor::calculate_slidingWindowAverage,this,_1,windowSize));
			sw_average_pub_ = n_.advertise<std_msgs::Float64>("/slidingWindowAverage_"+topicSuffix,1);
		}		


		void calculate_slidingWindowAverage(const std_msgs::Float64::ConstPtr& msg, int slidingWindowSize){
			double newVal = msg->data;
			double sum = 0;
			std_msgs::Float64 sw_average_msg_;
			// std::cout<<sw_average_msg_.data<<"PrintedSOmething\n";

			if(slidingWindowValues.size()==slidingWindowSize){
				//sum of elements in the vector
				sum = std::accumulate(slidingWindowValues.begin(),slidingWindowValues.end(),0.0);

				//Publish sliding window average
				sw_average_msg_.data = sum/slidingWindowSize;
				// std::cout<<sw_average_msg_.data<<"PrintedSOmething\n";
				sw_average_pub_.publish(sw_average_msg_);

				slidingWindowValues.erase(slidingWindowValues.begin());
				if(!isnan(newVal))
					slidingWindowValues.push_back(newVal);
			}
			else{
				if(!isnan(newVal))
					slidingWindowValues.push_back(newVal);	
			}
		}
};

int main(int argc, char *argv[]){
	ros::init(argc, argv, "slidingWindowAverageCalculator");
	ros::NodeHandle nh("~");
	std::string topicName,topicSuffix;
	int windowSize;

	nh.getParam("topic", topicName); //Please specify the topic you want to calculate the sliding window average for
	nh.getParam("windowSize", windowSize);// You can regulate the window size here. I usually go for 32 values.
	nh.getParam("topicSuffix", topicSuffix); // Inevitably people are going to apply the same support scripts to multiple topics. This suffix can differentiate them.
	signalProcessor sp1(topicName,windowSize,topicSuffix);
	ros::spin();
}