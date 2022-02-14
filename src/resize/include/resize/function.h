#include "resize/headers.h"

class Resize
{
    public:
        ros::NodeHandle n;

        ros::Publisher img_pub;

        std::string format;

        void callback(const sensor_msgs::ImagePtr &msg)
        {
            cv::Mat img;
            cv::Mat resize_img;
            
            std_msgs::Header head;

            sensor_msgs::ImagePtr img_msg;

            head.frame_id = msg->header.frame_id;
            head.seq = msg->header.seq;
            head.stamp = ros::Time::now();

            img = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;

            // resize_img = cv::Mat::zeros(img.cols/2.0, img.rows/2.0, img.type());
            cv::resize(img, resize_img, cv::Size(img.cols / 2.0, img.rows / 2.0), 0, 0, cv::INTER_LINEAR);

            img_msg = cv_bridge::CvImage(head, format, resize_img).toImageMsg();

            img_msg->height = resize_img.rows;
            img_msg->width  = resize_img.cols;


            img_pub.publish(img_msg);
            
            // cv::imshow("resized", resize_img);            

            // cv::waitKey(1);
        }

    Resize()
    {
        img_pub = n.advertise<sensor_msgs::Image>("/camera/rgb/image_resized_raw", 10);
        format = "bgr8";
    }
    ~Resize()
    {
    }
};