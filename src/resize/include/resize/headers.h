#include "ros/ros.h"
#include "compressed_image_transport/compressed_publisher.h"
#include "compressed_image_transport/compression_common.h"
#include "opencv2/imgproc/imgproc.hpp"

#include <image_transport/image_transport.h>
#include <iostream>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <std_msgs/String.h>
#include <mutex>
#include <algorithm>
#include <vector>