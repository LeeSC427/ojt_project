#ifndef SENSOR_HPP
#define SENSOR_HPP
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <thread>
#include <mutex>
#include <sensor_msgs/Image.h>

#include "public/templete.hpp"
#include "public/Params.hpp"

namespace allen
{
    class camera
    {
    public:
        ros::Subscriber rgb_gaussian_sub_;
        ros::Subscriber rgb_resized_sub_;
        allen::Image img_gaussian;
        allen::Image img_resized;

        camera()
        {
            this->img_gaussian = allen::Image("gaussian", 3, 480, 640);
            this->img_resized = allen::Image("resized", 3, 480, 640);
        }

    };
    class sensor
    {
    private:
        void initParams(ros::NodeHandle& _nh);

    public:
        ros::NodeHandle nh_;
        allen::camera c920;
        std::string module_name;
        pf::Params params;

        sensor(const std::string &_module_name) :
            module_name(_module_name)
        {
            this->params = pf::Params(this->module_name);
            this->initParams(nh_);
            this->init_Subscriber();
        }
        sensor(void){}
        void init_Subscriber();
        void rgb_callback(const sensor_msgs::Image::ConstPtr &msg, allen::Image *_src);

    };
}
#endif