/*
 * tutorial_8_random_binary_image.cpp
 *
 *  Created on: Jun 14, 2018
 *      Author: Ruikun
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

#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>
#include <functional>
#include <cstdint>
#include <cmath>

namespace {

using namespace std;
using cv::Mat;
using cv::imread;
using cv::Point;
using cv::Scalar;
using cv::Size;


vector<Mat> makeImages(size_t n, Size size, int imgType) {
    vector<Mat> out{};
    for (size_t i = 0; i < n; ++i) {
        out.push_back( Mat{size, imgType} );
    }
    return out;
}


void drawRandomRectangle( Mat& img, int low, int high, const Scalar& color, int N = 1, int thickness = CV_FILLED ) {
    auto width  = img.size().width;
    auto height = img.size().height;
    std::random_device rd;
    std::default_random_engine generator{rd()};
    std::uniform_int_distribution<int> sizeDist{low,high};
    std::uniform_int_distribution<int> xDist{0, width};
    std::uniform_int_distribution<int> yDist{0, height};

    int count = 0;

    while (count < N) {
        auto x1 = xDist( generator );
        auto y1 = yDist( generator );

        auto x2 = x1 + sizeDist( generator );
        auto y2 = y1 + sizeDist( generator );

        if (x2 < width && y2 < height) {
            Point p1{ x1, y1 };
            Point p2{ x2, y2 };
            rectangle( img, p1, p2, color, thickness );
            ++count;
        }
    }
}

void drawRandomLine( Mat& img, double maxLength, const Scalar& color, int N = 1, int thickness = 1) {
    auto width  = img.size().width;
    auto height = img.size().height;
    std::random_device rd;
    std::default_random_engine generator{rd()};
    std::uniform_int_distribution<int> xDist{0, width};
    std::uniform_int_distribution<int> yDist{0, height};

    int count = 0;

    while (count < N) {
        auto x1 = xDist( generator );
        auto y1 = yDist( generator );
        auto x2 = xDist( generator );
        auto y2 = yDist( generator );

        auto dx = x1 - x2;
        auto dy = y1 - y2;
        auto l = sqrt( dx * dx + dy * dy );

        if ( l < maxLength ) {
            Point p1{ x1, y1 };
            Point p2{ x2, y2 };
            line( img, p1, p2, color, thickness );
            ++count;
        }
    }
}



int main() {
    int width = 500;
    int height = 500;

    // create an image
    Mat img{Size(width, height), CV_8UC1, Scalar(0)};
    Scalar color{255};

    drawRandomRectangle( img, 15, 35, color, 20 );
    drawRandomRectangle( img, 5, 10, color, 50 );
    drawRandomLine( img, 40, color, 15, 2);
    drawRandomLine( img, 100, color, 20, 1);

    cv::imwrite("./data/random_binary_5.png", img);
//    cv::namedWindow("sample", cv::WINDOW_AUTOSIZE);
//    cv::imshow("sample", img);
//    cv::waitKey();

    return 0;
}

} // end of namespace
