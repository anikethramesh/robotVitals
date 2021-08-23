// //ROS
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <iostream>
// #include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
// #include <conio.h>
class keyPressChecker{
private:
	ros::NodeHandle n_;
	ros::Publisher keyPress_pub_;
	bool flag;
	std_msgs::Bool msg;
	public:
		// This is a function to check for spacebar press. It waits for a while and then assumes no input was given. change the timeout duration by using timeout.tv_usec
		char getch()
		{
			fd_set set;
			struct timeval timeout;
			int rv;
			char buff = 0;
			int len = 1;
			int filedesc = 0;
			FD_ZERO(&set);
			FD_SET(filedesc, &set);

			timeout.tv_sec = 0;
			timeout.tv_usec = 1000;

			rv = select(filedesc + 1, &set, NULL, NULL, &timeout);

			struct termios old = {0};
			if (tcgetattr(filedesc, &old) < 0)
				ROS_ERROR("tcsetattr()");
			old.c_lflag &= ~ICANON;
			old.c_lflag &= ~ECHO;
			old.c_cc[VMIN] = 1;
			old.c_cc[VTIME] = 0;
			if (tcsetattr(filedesc, TCSANOW, &old) < 0)
				ROS_ERROR("tcsetattr ICANON");

			if(rv == -1)
				ROS_ERROR("select");
			else if(rv == 0)
				ROS_INFO("no_key_pressed");
			else
				read(filedesc, &buff, len );

			old.c_lflag |= ICANON;
			old.c_lflag |= ECHO;
			if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
				ROS_ERROR ("tcsetattr ~ICANON");
			return (buff);
		}

		keyPressChecker(){
			keyPress_pub_ = n_.advertise<std_msgs::Bool>("/spacebar_pressed",1);
			ros::Rate r(2);
			flag = false;
			while(ros::ok()){
					char c = getch();
					if(c==32||c==' '){
						flag = !flag;
					}
				std::cout<<"Status: "<<flag<<"\n";
				msg.data = flag;
				keyPress_pub_.publish(msg);
				r.sleep();
			}
		}
};


int main(int argc, char *argv[]){
	ros::init(argc, argv, "SpaceBar_checker");
	ros::NodeHandle nh("~");
	keyPressChecker kp;
	ros::spin();
	
} 
