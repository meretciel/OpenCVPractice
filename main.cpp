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


int main() {
    cout << "openCV version: " << CV_VERSION << endl;

    string filename{"./data/fractal_3.png"};

    cout << "read file: " << filename << endl;
    Mat image = imread(filename, cv::IMREAD_COLOR);

    cout << "number of channels: " << image.channels() << endl;
    cout << "depth of image: " << image.depth() << endl;
    cout << "element type of Mat: " << image.type() << endl;
    cout << "name of element type: " << utils::getTypeName( image.type() ) << endl;

    int nrows = image.rows;
    int ncols = image.cols;
    auto size = image.size();
    int height = size.height;
    int width  = size.width;

    cout << "nrows:  " << nrows  << endl
         << "ncols:  " << ncols  << endl
         << "height: " << height << endl
         << "width:  " << width  << endl;

    // visulaize images
//    cv::namedWindow("fractal", cv::WINDOW_AUTOSIZE);
//    cv::imshow("fractal", image);
//    cv::waitKey();

    return 0;

}
