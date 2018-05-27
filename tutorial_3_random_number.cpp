/*
 * tutorial_3_random_number.cpp
 *
 *  Created on: May 27, 2018
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

#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>
#include <functional>
#include <cstdint>


using namespace std;
using cv::Mat;
using cv::imread;
using cv::Point;
using cv::Scalar;
using cv::Size;


namespace {

int main() {
    std::random_device rd;
    std::default_random_engine generator{rd()};
    std::uniform_int_distribution<int> dist{0,255};
    auto rand = [&]()->uchar{ return static_cast<uchar>(dist(generator)); };

    int n = 10;
    for (int i = 0; i < n; ++i) {
        cout << std::to_string( rand() ) << endl;
    }

    return 0;
}


} // end of namespace
