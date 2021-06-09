// #include"ros/ros.h"
// #include<std_msgs/Float64.h>
// #include<std_msgs/String.h>

// #include<boost/bind.hpp>

// #include<cmath>
// #include<time.h>

// class tester{
// 	private:
// 			ros::NodeHandle n_;
// 			ros::Publisher output_pub_;

// 			ros::Subscriber sub1_, sub2_;

// 			ros::Timer timer;

// 			double val1, val2;

// 	public: 
// 			tester(){
// 				timer = n_.createTimer(ros::Duration(0.5),&tester::output_callback,this);
// 				sub1_ = n_.subscribe<std_msgs::Float64>("/value1",10,&tester::val1_callback,this);
// 				sub2_ = n_.subscribe<std_msgs::Float64>("/value2",10,&tester::val2_callback,this);
// 				output_pub_ = n_.advertise<std_msgs::Float64>("/outputValue",10);
// 			}

// 			void val1_callback(const std_msgs::Float64::ConstPtr& msg){
// 				val1 = msg->data;
// 			}

// 			void val2_callback(const std_msgs::Float64::ConstPtr& msg){
// 				val2 = msg->data;
// 			}

// 			void output_callback(const ros::TimerEvent& event){
// 				// ROS_DEBUG("The output is %d", val1 - val2);
// 				std_msgs::Float64 output_msg_;
// 				output_msg_.data = val1 - val2;
// 				output_pub_.publish(output_msg_);
// 			}
// };

// int main(int argc,char *argv[]){
// 	ros::init(argc,argv,"samplerDemo");
// 	tester t1;
// 	ros::spin();
// }


//ROS
#include <ros/ros.h>
#include <ros/console.h>
// #include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/PoseStamped.h>
// Binding arguments for callback
#include <boost/bind.hpp>

//general
#include <cmath>
#include <time.h>
#include <vector>
#include <numeric>
#include <string>

class vitalsPreprocessor{
	private:
		ros::NodeHandle n_;
		ros::Publisher pub_odomError_, pub_imu_linAccZ_, pub_magDistFromGoal_;
		ros::Subscriber sub_huskyVelocityController_odom_, sub_odometryFiltered_, sub_currentGoal_moveBase_, sub_imu_linearAcc_;
		// ros::Timer timer_odomError, timer_imuLinAccZ, timer_magDistFromGoal_;

		//Variables to store the values
		geometry_msgs::Point position_odometryFiltered, position_odometryHuskyVelController, position_currentGoalMoveBase;
		geometry_msgs::Vector3 imu_linearAcc;

		//timer functions for sampling the variables
		ros::Timer sampler;

	public:
		vitalsPreprocessor(){
			sub_odometryFiltered_ = n_.subscribe<nav_msgs::Odometry>("/odometry/filtered",10,&vitalsPreprocessor::callback_odomFiltered,this);
			sub_huskyVelocityController_odom_ = n_.subscribe<nav_msgs::Odometry>("/husky_velocity_controller/odom",10,&vitalsPreprocessor::callback_odomHuskyVelController,this);
			sub_currentGoal_moveBase_ = n_.subscribe<geometry_msgs::PoseStamped>("/move_base/current_goal",10,&vitalsPreprocessor::callback_currentGoal,this);
			sub_imu_linearAcc_ = n_.subscribe<sensor_msgs::Imu>("/imu/data",10,&vitalsPreprocessor::callback_linearAcc,this);
			pub_odomError_ = n_.advertise<std_msgs::Float64>("/odom_posErr_sampled",10);
			pub_imu_linAccZ_ = n_.advertise<std_msgs::Float64>("/mag_distFromGoal_sampled",10);
			pub_magDistFromGoal_ = n_.advertise<std_msgs::Float64>("/linAcc_Z_sampled",10);
			sampler = n_.createTimer(ros::Duration(0.5),&vitalsPreprocessor::callback_rvPublisher,this);
		}

		//callbacks to store the variables
		void callback_odomFiltered(const nav_msgs::Odometry::ConstPtr& msg){
			position_odometryFiltered = msg->pose.pose.position;
		}

		void callback_odomHuskyVelController(const nav_msgs::Odometry::ConstPtr& msg){
			position_odometryHuskyVelController = msg->pose.pose.position;
		}

		void callback_currentGoal(const geometry_msgs::PoseStamped::ConstPtr& msg){
			position_currentGoalMoveBase = msg->pose.position;
		}

		void callback_linearAcc(const sensor_msgs::Imu::ConstPtr& msg){
			imu_linearAcc = msg->linear_acceleration;
		}

		//calculations
		geometry_msgs::Vector3 calculate_odomPosErr(){
			geometry_msgs::Vector3 posErr;
			posErr.x = position_odometryHuskyVelController.x - position_odometryFiltered.x;
			posErr.y = position_odometryHuskyVelController.y - position_odometryFiltered.y;
			posErr.z = position_odometryHuskyVelController.z - position_odometryFiltered.z;
			return posErr;
		}

		geometry_msgs::Vector3 calculate_magDistFromGoal(){
			geometry_msgs::Vector3 magDist;
			magDist.x = position_currentGoalMoveBase.x - position_odometryFiltered.x;
			magDist.y = position_currentGoalMoveBase.y - position_odometryFiltered.y;
			magDist.z = position_currentGoalMoveBase.z - position_odometryFiltered.z;
			return magDist;
		}

		void callback_rvPublisher(const ros::TimerEvent& event){
			// ROS_DEBUG("The output is %d", val1 - val2);
			// std_msgs::Float64 output_msg_;
			// output_msg_.data = val1 - val2;
			// std_msgs::Float64 output_msg_;
			// output_msg_.data = val1 - val2;
			// output_pub_.publish(output_msg_);
			geometry_msgs::Vector3 posErr, magDist;
			posErr = calculate_odomPosErr();
			magDist = calculate_magDistFromGoal();
			std_msgs::Float64 msg_odomPosError, msg_magDistFromGoal, msg_linAccZ;
			msg_odomPosError.data = sqrt(pow(posErr.x,2)+ pow(posErr.y,2) + pow(posErr.z,2));
			msg_magDistFromGoal.data = sqrt(pow(magDist.x,2)+ pow(magDist.y,2) + pow(magDist.z,2));
			msg_linAccZ.data = imu_linearAcc.x;

			pub_odomError_.publish(msg_odomPosError);
			pub_magDistFromGoal_.publish(msg_magDistFromGoal);
			pub_imu_linAccZ_.publish(msg_linAccZ);
		}
};

int main(int argc,char *argv[]){
	ros::init(argc,argv,"rv_sampler");
	vitalsPreprocessor vp1;
	ros::spin();
}