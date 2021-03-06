#include "Gaussian/headers.h"

std::string save_path="/home/cona/gaussian_picture/gaussian[";
int num=0;
ros::Subscriber Subscribe_Compressed_image;
ros::Publisher Publish_Gaussian_image;
// ros::Publisher Publish_Resized_image;
sensor_msgs::Image sub_image_msg;

void imageCallback(const sensor_msgs::Image::ConstPtr& scan);
std::string make_string();

int main(int argc, char**argv)
{
    ros::init(argc,argv,"visualizer_node");
    ros::NodeHandle n;
    Subscribe_Compressed_image=n.subscribe("image_data",10,imageCallback);
    Publish_Gaussian_image=n.advertise<sensor_msgs::Image>("/camera/rgb/image_gaussian_raw",10);
    // Publish_Resized_image=n.advertise<sensor_msgs::Image>("topic_resized",10);
    
    while(ros::ok())
    {
        cv::waitKey(1);        
        ros::spinOnce();
    }
    return 0;
}

void imageCallback(const sensor_msgs::Image::ConstPtr& scan)
{
    sub_image_msg=*scan;
    std::cout << "got image data"<<std::endl;

    //cv::Mat matrix = cv::imdecode(cv::Mat(sub_image_msg.data),1);//수정바람
    cv::Mat matrix;
    cv_bridge::CvImagePtr matrix_ptr = cv_bridge::toCvCopy(sub_image_msg,"bgr8");
    matrix=matrix_ptr->image;

    cv::Mat gaussian_image;
    // cv::Mat resized_image;
            
    // cv::resize(matrix,resized_image,cv::Size(),0.5,0.5);
    cv::GaussianBlur(matrix,gaussian_image,cv::Size(),3);

    // cv::namedWindow("gaussian_image");
    // cv::moveWindow("gaussian_image",matrix.rows*2,0);
    // cv::imshow("gaussian_image",gaussian_image);

    // cv::namedWindow("resized_image");
    // cv::moveWindow("resized_image",matrix.rows*3,0);
    // cv::imshow("resized_image",resized_image);
            
    // cv::imwrite(make_string(),gaussian_image);

    sensor_msgs::ImagePtr gaussian_image_msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",gaussian_image).toImageMsg();
    Publish_Gaussian_image.publish(gaussian_image_msg);
    // sensor_msgs::ImagePtr resized_image_msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",resized_image).toImageMsg();
    // Publish_Resized_image.publish(resized_image_msg);
    num++;
}
std::string make_string()
{
    std::string temp_string=save_path+std::to_string(num)+"].jpeg";
    return temp_string;
}