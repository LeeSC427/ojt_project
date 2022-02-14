#include "resize/function.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "resize");

    std::string topic_name = "/image_data";

    ros::NodeHandle nh;
    ros::NodeHandle n_private("~");

    n_private.param<std::string>("/image_data", topic_name, "/image_data");

    Resize resize;

    ros::Subscriber sub = nh.subscribe(topic_name, 10, &Resize::callback, &resize);
    
    ros::spin();
    
    return 0;
}