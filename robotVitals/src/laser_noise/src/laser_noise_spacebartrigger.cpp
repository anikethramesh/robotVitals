#include<ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Bool.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
class LaserNoise{
	private:
		ros::NodeHandle n_;
		ros::Subscriber laser_sub_;
		ros::Publisher scan_with_noise_pub_, laser_noise_active_pub_;
		ros::Timer timer_noise_;
		bool timer_trigger_;
		double noise_scale_;
		double counter = 1;
	public:
		LaserNoise(){			
			// private_nh.param("noise_period", noise_period_, 30.0)
			laser_sub_ = n_.subscribe<sensor_msgs::LaserScan>("scan", 20, &LaserNoise::laserReadCallBack, this);

			scan_with_noise_pub_ = n_.advertise<sensor_msgs::LaserScan>("scan_with_noise", 20);
			laser_noise_active_pub_ = n_.advertise<std_msgs::Bool>("laser_noise_active", 20);

			timer_noise_ = n_.createTimer(ros::Duration(20), &LaserNoise::timerNoiseCallback, this);
			timer_trigger_ = false;
			noise_scale_ = 0.3;
		}

		void timerNoiseCallback(const ros::TimerEvent&)
		{
			timer_trigger_ = !timer_trigger_;
			if(timer_trigger_){
				noise_scale_ = 0.05*counter;
				++counter;
			}
			// timer_noise_.stop();
			// ROS_INFO("TIMER ACTIVATED");
		}

		// Utility function for adding Guassian noise
		double GaussianKernel(double mu,double sigma)
		{
			// using Box-Muller transform to generate two independent standard normally disbributed normal variables

			double U = (double)rand()/(double)RAND_MAX; // normalized uniform random variable
			double V = (double)rand()/(double)RAND_MAX; // normalized uniform random variable
			double X = sqrt(-2.0 * ::log(U)) * cos( 2.0*M_PI * V);
			//double Y = sqrt(-2.0 * ::log(U)) * sin( 2.0*M_PI * V); // the other indep. normal variable
			// we'll just use X
			// scale to our mu and sigma
			X = sigma * X + mu;
			return X;
		}

		// reads published by laser scans and adds noise to them
		void laserReadCallBack(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
		{
			double sigma;
			double old_range;
			std_msgs::Bool noise;
			sensor_msgs::LaserScan laser_scan = *scan_msg;

			// Guassian noise added
			if(timer_trigger_)
			{
				for (int i=0; i < laser_scan.ranges.size(); i++)
				{
					sigma = laser_scan.ranges[i] * noise_scale_; // Proportional standard deviation
					old_range = laser_scan.ranges[i];
					laser_scan.ranges[i] = laser_scan.ranges[i] + GaussianKernel(0,sigma);

					if (laser_scan.ranges[i] > laser_scan.range_max)
					{ laser_scan.ranges[i] = laser_scan.range_max; }

					else if (laser_scan.ranges[i] < laser_scan.range_min)
					{ laser_scan.ranges[i] = old_range; }
				}
				noise.data = true;
				laser_noise_active_pub_.publish(noise);
				ROS_INFO("Laser noise is active");
			}
			else
			{
				noise.data = false;
				laser_noise_active_pub_.publish(noise);
			}
			laser_scan.header.stamp = ros::Time::now();
			scan_with_noise_pub_.publish(laser_scan);
		}

};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "laser_noise");
	LaserNoise lasernoise;
	ros::spin();
}