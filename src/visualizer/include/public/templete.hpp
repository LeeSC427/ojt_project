#ifndef TEMPLETE_HPP
#define TEMPLETE_HPP
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
namespace allen
{
    class Image
    {
    public:
        class params
        {
        public:
            struct extrinsic
            {
            public:
                cv::Point3d translate;
                double roll, pitch, yaw;
            };
            cv::Mat K;      //intrinsic parameter
            extrinsic R;    //extricsic parameter
            cv::Mat P;      //projection matrix
            params()
            {
                K = cv::Mat::eye(3, 3, CV_64FC1);
                P = cv::Mat::zeros(3, 4, CV_64FC1);
                set_K();
                set_R();
            }
            void set_K()
            {
                this->K.at<double>(0, 0) = 478.32086;   //fx
                this->K.at<double>(0, 2) = 318.0971;    //cx
                this->K.at<double>(1, 1) = 478.32086;   //fy
                this->K.at<double>(1, 2) = 193.52925;   //cy
            }
            void set_R()
            {
                this->R.translate.x = 0.0;      //side to side
                this->R.translate.y = 940.0;    //camera to plane
                this->R.translate.z = 280.0;    //base_link to camera
                this->R.roll = 0.0;
                this->R.pitch = 0.0;
                this->R.yaw = 0.0;
            }
        };

        params param_;
        int rows, cols;
        int channel_;
        cv::Mat Raw_mat, Plot_mat;
        std::string win_name;

        Image(const std::string& _win_name, int _channel, int _rows=480, int _cols=640) :
            win_name(_win_name),
            rows(_rows), cols(_cols),
            channel_(_channel)
        {
            this->Raw_mat = cv::Mat(rows, cols, channel_, cv::Scalar(0));
            this->Plot_mat = cv::Mat(rows, cols, channel_, cv::Scalar(0));
        }
        Image()
        {}
        ~Image()
        {
            this->Raw_mat = cv::Mat();
            this->Plot_mat = cv::Mat();
        }

    };

}
#endif