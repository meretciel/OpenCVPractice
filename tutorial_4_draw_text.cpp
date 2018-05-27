

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
    int height = 600;
    int width = 800;

    Mat img{ height, width, CV_8UC3, Scalar(0,0,0) };

    Point origin{240,200};
    string text{"Hello OpenCV!"};

    putText(img, text, origin, cv::FONT_HERSHEY_COMPLEX_SMALL, 1., Scalar(0,255,0), 1, cv::LINE_8);
    cv::imwrite("./data/opencv_text.png", img);
    cout << "finished." << endl;

//    cv::namedWindow("text", cv::WINDOW_AUTOSIZE);
//    cv::imshow("text", img);
//    cv::waitKey();
    return 0;
}

} // end of namespace
