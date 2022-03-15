//
//  filter.hpp
//  Project1
//
//  Created by Ankitha Udupa on 2/8/22.
//

#ifndef filter_hpp
#define filter_hpp
#include"opencv2/core.hpp"

#include <stdio.h>
int greyscale(cv::Mat &src, cv::Mat &dst);
int blur5x5( cv::Mat &src, cv::Mat &dst );
int sobelX3x3( cv::Mat &src, cv::Mat &dst );
int sobelY3x3( cv::Mat &src, cv::Mat &dst );
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );
int brightness(cv::Mat &src, cv::Mat&dst, int brightness);
int rgb_hsv(cv::Mat &img);
#endif /* filter_hpp */
