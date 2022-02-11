#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <thread>
#include <mutex>

#include "public/sensor.hpp"
#include "public/Params.hpp"

namespace allen
{
    class visualizer
    {
    private:
        int loop_rate_;
        void run_plot(void);
        void plot(void);

    public:
        std::thread *thread_visualizer_;
        allen::sensor *sensors;
        visualizer()
        {
            this->sensors = new allen::sensor("/visualizer");
        }
        ~visualizer()
        {
            delete this->thread_visualizer_;
            delete this->sensors;
        }
        void connect(const int& _rate);

    };
}
#endif