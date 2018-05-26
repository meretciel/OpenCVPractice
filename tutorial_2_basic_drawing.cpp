

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


namespace {

int main() {
    cout << "openCV version: " << CV_VERSION << endl;
    
    Point point{10, 20};
    cout << "point object: (" << point.x << ", " << point.y << ")" << endl;
    
    Scalar scalar{0,0,225};
    for (int i = 0; i < 4; ++i) {
        cout << "scalar[" << i << "] = " << scalar[i] << endl;
    }
    scalar[3] = 10;
    cout << "new scalar[3] = " << scalar[3] << endl;

    // basic drawing
    int height = 600;
    int width  = 600;

    // create a new image
    Mat blackImage{Mat::zeros(height, width, CV_8UC3)};
    Mat whiteImage{height, width, CV_8UC3, Scalar(255,255,255)};
    
    // draw a line on the black image
    Point start{200, 200};
    Point end{width/2, height/2};

    int thickness = 2;
    int lineType = cv::LINE_8;
    cv::line(blackImage, start, end, Scalar(255,0,0), thickness, lineType);


    // draw a filled circle
    Point center{width/2, height/2};
    int radius = width/42;

    circle(blackImage, center, radius, Scalar(0,0,255), cv::FILLED, cv::LINE_8);

    // draw ellipses
    // size controls the shape of the ellipse
    Size  size{width/4, width/16};

    for(auto angle : {0,45,90, 135}) {
        cv::ellipse(blackImage, center, size, angle, 0,360, Scalar(255,0,0), thickness, lineType);
    }

    cv::namedWindow("blackImage", cv::WINDOW_AUTOSIZE);
    cv::imshow("blackImage", blackImage);
    cv::waitKey();

    return 0;

}

} // end of namespace
