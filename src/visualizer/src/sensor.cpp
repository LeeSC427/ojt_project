#include "public/sensor.hpp"

void allen::sensor::initParams(ros::NodeHandle& _nh)
{
    try
    {
        this->params.add_params("/topic_gaussian", std::string{"/camera/rgb/image_gaussian_raw"});
        this->params.add_params("/topic_resized", std::string{"/camera/rgb/image_resized_raw"});
        this->params.read_params(_nh);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void allen::sensor::init_Subscriber()
{
    try
    {
        ROS_WARN("params: /topic_gaussian, %s-> advertising..", this->params.get_str("/topic_gaussian").c_str());
        ROS_WARN("params: /topic_resized, %s-> advertising..", this->params.get_str("/topic_resized").c_str());
        this->c920.rgb_gaussian_sub_ = this->nh_.subscribe<sensor_msgs::Image>(this->params.get_str("/topic_gaussian"), 
                                    10, boost::bind(&sensor::rgb_callback, this, _1, &c920.img_gaussian));
        this->c920.rgb_resized_sub_ = this->nh_.subscribe<sensor_msgs::Image>(this->params.get_str("/topic_resized"), 
                                    10, boost::bind(&sensor::rgb_callback, this, _1, &c920.img_resized));
    }
    catch(ros::InvalidNameException e)
    {
        ROS_ERROR("Fail to init publisher: %s", std::string(e.what()).c_str());
    }
}
void allen::sensor::rgb_callback(const sensor_msgs::Image::ConstPtr &msg, allen::Image *_src)
{
    _src->rows = msg->height;
    _src->cols = msg->width;
    unsigned char msg_video[_src->rows * _src->cols * _src->channel_];

    for(int i = 0; i < (int)msg->data.size(); i++)
        msg_video[i] = msg->data[i];
    cv::Mat tmp_bgr, tmp_rgb;
    tmp_bgr = cv::Mat(_src->rows, _src->cols, CV_8UC3, msg_video);

    _src->Raw_mat = tmp_bgr.clone();
    _src->Plot_mat = tmp_bgr.clone();
}