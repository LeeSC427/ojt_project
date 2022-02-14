
#include "camera.hpp"

ros::Subscriber Subscribe_image;
sensor_msgs::Image my_image;
cv::Mat image;
void imageCallback(const sensor_msgs::Image::ConstPtr &scan);

int main(int argc, char**argv)
{
    ros::init(argc,argv,"giveme_image_node");
    ros::NodeHandle n;
    Subscribe_image=n.subscribe("resize_data",10,imageCallback);

    while(ros::ok())
    {
        cv::waitKey(1);        
        ros::spinOnce();
    }
    return 0;
}
void imageCallback(const sensor_msgs::Image::ConstPtr &scan)
{
    my_image=*scan;
    cv_bridge::CvImagePtr matrix_ptr = cv_bridge::toCvCopy(my_image,"bgr8");
    image=matrix_ptr->image;
    cv::namedWindow("gaussian_image_recieve");
    cv::moveWindow("gaussian_image_recieve",100,100);
    cv::imshow("gaussian_image_recieve",image);
}
