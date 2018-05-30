

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


    Mat mat1{Size(100,120), CV_8UC3};
    cout << "mat1{Size(100,120), CV_8UC3}" << endl;
    cout << "height: " << mat1.rows << ", " << mat1.size().height << endl;
    cout << "width:  " << mat1.cols << ", " << mat1.size().width << endl << endl;

    Mat mat2{Size(100, 120), CV_8UC2, Scalar(0,0,0)};
    cout << "mat2{Size(100,120), CV_8UC3, Scalar(0,0,0)}" << endl;
    cout << "height: " << mat2.rows << ", " << mat2.size().height << endl;
    cout << "width:  " << mat2.cols << ", " << mat2.size().width << endl << endl;


    Mat mat3{120,100, CV_8UC3};
    cout << "mat3{120,100, CV_8UC3}" << endl;
    cout << "height: " << mat3.rows << ", " << mat3.size().height << endl;
    cout << "width:  " << mat3.cols << ", " << mat3.size().width << endl << endl;

    Mat mat4{120,100, CV_8UC3, Scalar(0,0,0)};
    cout << "mat4{120,100, CV_8UC3, Scalar(0,0,0)}" << endl;
    cout << "height: " << mat4.rows << ", " << mat4.size().height << endl;
    cout << "width:  " << mat4.cols << ", " << mat4.size().width << endl;

    cout << "finishied" << endl;

    return 0;
}

} // end of namespace
