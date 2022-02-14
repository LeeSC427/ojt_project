#include "visualizer/visualizer.hpp"


void allen::visualizer::connect(const int& _rate)
{
    this->loop_rate_ = _rate;
    this->thread_visualizer_ = new std::thread([this]{run_plot();});
}
void allen::visualizer::plot(void)
{
    cv::Mat plot_gaussian = this->sensors->c920.img_gaussian.Plot_mat.clone();
    cv::Mat plot_resized = this->sensors->c920.img_resized.Plot_mat.clone();
    if(plot_gaussian.empty())                               return;
    if(plot_resized.empty())                                return;
    if(plot_gaussian.cols < 0 || plot_resized.cols < 0)     return;

    // std::cout << plot_gaussian << std::endl;

    // std::cout << plot_resized << std::endl;
    
    cv::imshow(this->sensors->c920.img_gaussian.win_name, plot_gaussian);
    cv::imshow(this->sensors->c920.img_resized.win_name, plot_resized);
    cv::waitKey(1);
}
void allen::visualizer::run_plot(void)
{
    ros::Rate r(this->loop_rate_);
    while (ros::ok())
    {
        /* code */
        plot();
        r.sleep();
    }
}