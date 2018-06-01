

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

    Mat img = imread("./data/screenshot_20180525.png", cv::IMREAD_COLOR);

    auto size = img.size();
    cout << "original image: height = " << size.height << ", width: " << size.width << endl;

    
    Mat dst_20{ img.size(), img.type() };
    Mat dst_60{ img.size(), img.type() };

    int kernelWidth = 20;
    cv::blur( img, dst_20, Size( kernelWidth, kernelWidth), Point(-1,-1));

    kernelWidth = 60;
    cv::blur( img, dst_60, Size( kernelWidth, kernelWidth), Point(-1,-1));

    auto horizontalCombined = utils::concat(vector<Mat>{dst_20, dst_60}, 0);
    auto verticalCombined   = utils::concat(vector<Mat>{dst_20, dst_60}, 1);

    cout << "horizontal combined image: height = " << horizontalCombined.size().height << ", width: " << horizontalCombined.size().width << endl;
    cout << "vertical combined image: height = " << verticalCombined.size().height << ", width: " << verticalCombined.size().width << endl;

    cv::namedWindow("original", cv::WINDOW_NORMAL);
    cv::imshow("original", img);
    
    cv::namedWindow( "horizontal", cv::WINDOW_NORMAL);
    cv::imshow("horizontal", horizontalCombined);

    cv::namedWindow( "vertical", cv::WINDOW_NORMAL);
    cv::imshow("vertical", verticalCombined);

    cv::waitKey();
//    cv::imwrite("../data/_sample_output.png", img);
    return 0;
}

} // end of namespace
