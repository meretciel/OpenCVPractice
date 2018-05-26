/*
 * main.cpp
 *
 *  Created on: May 25, 2018
 *      Author: ruikun
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "utils.h"


using namespace std;
using cv::Mat;
using cv::imread;
using cv::Point;
using cv::Scalar;
using cv::Size;

int main() {

    int height = 600;
    int width  = 600;

    // create a new image
    Mat blackImage{Mat::zeros(height, width, CV_8UC3)};
    
    // draw a filled circle
    Point center{width/2, height/2};
    int radius = width/42;

    circle(blackImage, center, radius, Scalar(0,0,255), cv::FILLED, cv::LINE_8);

    // draw several ellipses
    // size controls the shape of the ellipse
    Size  size{width/4, width/16};
    int thickness = 2;

    for(auto angle : {0,45,90, 135}) {
        cv::ellipse(blackImage, center, size, angle, 0,360, Scalar(255,0,0), thickness, cv::LINE_8);
    }

    cv::imwrite("./data/atom.png", blackImage);
    cout << "finished." << endl;

    return 0;
}
