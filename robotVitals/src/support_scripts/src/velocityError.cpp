// #include <message_filters/subscriber.h>
// #include <message_filters/time_synchronizer.h>
// #include <sensor_msgs/Image.h>
// #include <sensor_msgs/CameraInfo.h>
// #include "tf/message_filter.h"
// #include <geometry_msgs/TwistStamped.h>


// // using namespace sensor_msgs;
// // using namespace message_filters;

// void callback(const geometry_msgs::TwistStamped& image, const sensor_msgs::CameraInfoConstPtr& cam_info)
// {
//   // Solve all of perception here...
// }

// int main(int argc, char** argv)
// {
//   ros::init(argc, argv, "vision_node");

//   ros::NodeHandle nh;

//   message_filters::Subscriber<sgeometry_msgs::TwistStamped> image_sub(nh, "image", 1);
//   message_filters::Subscriber<sensor_msgs::CameraInfo> info_sub(nh, "camera_info", 1);
//   message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::CameraInfo> sync(image_sub, info_sub, 10);
//   sync.registerCallback(boost::bind(&callback, _1, _2));

//   ros::spin();

//   return 0;
// }









#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Bool.h"
#include <ros/ros.h>
#include <ros/console.h>


class velocityProcessor{
	private:
		ros::NodeHandle n_;
		ros::Publisher vel_error_x_pub_;
		ros::Publisher dummy_pub_;
		ros::Subscriber sub1_,sub2_;
		ros::Timer compute_cost_;

		geometry_msgs::Twist cmd_vel_expert, cmd_vel_actual;
		std_msgs::Float64 vel_error_x;
		double vel_error_val;

		std_msgs::Float64 myData;
		double buff;

	public:
		velocityProcessor(){
			sub1_ = n_.subscribe<geometry_msgs::Twist>("/cmd_vel", 1, &velocityProcessor::robotVelCallback,this);
			sub2_ = n_.subscribe<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1, &velocityProcessor::robotVelExpertCallback,this);
			vel_error_x_pub_ = n_.advertise<std_msgs::Float64>("/vel_error_x",1);
			dummy_pub_ = n_.advertise<std_msgs::Float64>("/test_bool",1);
			compute_cost_ = n_.createTimer(ros::Duration(0.02), &velocityProcessor::get_velError,this);

			buff = 0;
			myData.data = buff;

		}

		void robotVelCallback(const geometry_msgs::Twist::ConstPtr& msg1){
			// cmd_vel_actual = msg->data;
			cmd_vel_actual = *msg1;
		}
		
		void robotVelExpertCallback(const geometry_msgs::Twist::ConstPtr& msg2){
			// cmd_vel_expert = msg->data;
			cmd_vel_expert = *msg2;
		}


		void get_velError(const ros::TimerEvent&){

			// myData.data = (myData.data)?false:true;
			myData.data = buff;
			dummy_pub_.publish(myData);
			++buff;
			// std_msgs::Float64 vel_error_x;
			// double value = cmd_vel_actual.linear.x - cmd_vel_expert.linear.x;
			vel_error_val = cmd_vel_actual.linear.x - cmd_vel_expert.linear.x;
			vel_error_x.data = vel_error_val;


			vel_error_x_pub_.publish(vel_error_x);
			ROS_INFO("\n actual %f, expert %f, variable %f, calculation %f",cmd_vel_actual.linear.x, cmd_vel_expert.linear.x, vel_error_val, vel_error_x.data);
			// ROS_INFO("\n actual %f",cmd_vel_actual - cmd_vel_expert);
		}
};

// geometry_msgs::Twist cmd_vel_expert, cmd_vel_actual;
// ros::Publisher vel_error_x_pub_;
// // ros::Publisher vel_error_z_pub_;

// void robotVelCallback(const geometry_msgs::Twist::ConstPtr& msg)
// {
//   cmd_vel_actual = *msg;

// }

// void robotVelExpertCallback(const geometry_msgs::Twist::ConstPtr& msg)
// {
//   cmd_vel_expert = *msg;

// }

void computeCostCallback(const ros::TimerEvent&){
	std_msgs::Float64 vel_error_x;//, vel_error_z;
	vel_error_x.data = (float)(cmd_vel_expert.linear.x - cmd_vel_actual.linear.x);
	// ROS_INFO("\nFirst: [%f]", cmd_vel_expert.linear.x - cmd_vel_actual.linear.x);
	// ROS_INFO("\nKata idhar: [%f]", vel_error_x.data);
	// vel_error.linear.y = cmd_vel_expert.linear.y - cmd_vel_actual.linear.y;
	// vel_error_z.data = cmd_vel_expert.linear.z - cmd_vel_actual.linear.z;
	// vel_error.angular.x = cmd_vel_expert.angular.x - cmd_vel_actual.angular.x;
	// vel_error.angular.y = cmd_vel_expert.angular.y - cmd_vel_actual.angular.y;
	// vel_error.angular.z = cmd_vel_expert.angular.z - cmd_vel_actual.angular.z;

	// vel_error_x_pub_.publish(vel_error_x.data);
	// vel_error_z_pub_.publish(vel_error_z);
	if((cmd_vel_expert.linear.x - cmd_vel_actual.linear.x)){		
		if(vel_error_x.data == (cmd_vel_expert.linear.x - cmd_vel_actual.linear.x))
			ROS_INFO("\nBingo baby!");
		else ROS_INFO("\nSadte rehna tu bhenchod");
	}
	else
		ROS_INFO("Chal mohana ranga");
	vel_error_x_pub_.publish(vel_error_x);
}

int main(int argc, char *argv[]){
	ros::init(argc, argv, "vel_error_calculator");
	ros::NodeHandle nh("~");
	velocityProcessor vp1;
	// ros::Rate r(10); // 10 hz
	// while (ros::ok()){
	// 	ros::spin();
	// 	r.sleep();
	// }
	ros::spin();
}
