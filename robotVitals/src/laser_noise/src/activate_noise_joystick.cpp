#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Bool.h"
#include <std_msgs/Int8.h>

class JoyActivate{
	private:
		// void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
		ros::NodeHandle nh_;

		ros::Publisher event_pub_;
		ros::Subscriber joy_sub_; 

		int count;
	public:
		JoyActivate(){
			event_pub_ = nh_.advertise<std_msgs::Int8>("/pdf_event",1);
			joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &JoyActivate::joyCallback, this);
			count = 0;
		}

		void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
		{
			std_msgs::Int8 msg;
			// int counter = 0;
			if(joy->buttons[0] == 1)
				count = 1;
			// 	counter=1;
			// else if(joy->buttons[1] == 1)
			// 	counter=2;
			// else if(joy->buttons[2] == 1)
			// 	counter=3;
			// else if(joy->buttons[3] == 1)
			// 	counter=4;
			else
				count=0;
			
			msg.data = count;
		  event_pub_.publish(msg);
		}
};

// class TeleopTurtle
// {
// public:
//   TeleopTurtle();

// private:
//   void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

//   ros::NodeHandle nh_;

//   int linear_, angular_;
//   double l_scale_, a_scale_;
//   ros::Publisher vel_pub_;
//   ros::Subscriber joy_sub_;

// };


// TeleopTurtle::TeleopTurtle():
//   linear_(1),
//   angular_(2)
// {

//   nh_.param("axis_linear", linear_, linear_);
//   nh_.param("axis_angular", angular_, angular_);
//   nh_.param("scale_angular", a_scale_, a_scale_);
//   nh_.param("scale_linear", l_scale_, l_scale_);


//   vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);


//   joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);

// }

// void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
// {
//   geometry_msgs::Twist twist;
//   twist.angular.z = a_scale_*joy->axes[angular_];
//   twist.linear.x = l_scale_*joy->axes[linear_];
//   vel_pub_.publish(twist);
// }


int main(int argc, char** argv)
{
  ros::init(argc, argv, "activate_noise_joystick");
  JoyActivate joy1;

  ros::spin();
}
