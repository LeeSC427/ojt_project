#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

#include "visualizer/visualizer.hpp"

int main(int argc, char**argv)
{
	ros::init(argc, argv, "visualizer");
	ROS_WARN("=== [%s]Welcome to 3rd OJT ===", ros::this_node::getName().c_str());

	allen::visualizer visual;
	ros::AsyncSpinner spinner(4);
	spinner.start();
	visual.connect(30);

	visual.thread_visualizer_->join();
	ros::waitForShutdown();

    return 0;
}
