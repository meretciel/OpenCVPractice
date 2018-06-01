

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

vector<Mat> makeImages(size_t n, Size size, int imgType) {
    vector<Mat> out{};
    for (size_t i = 0; i < n; ++i) {
        out.push_back( Mat{size, imgType} );
    }
    return out;
}


int main() {

    Mat img = imread("./data/find_icons.png", cv::IMREAD_COLOR);

    auto size = img.size();
    cout << "original image: height = " << size.height << ", width: " << size.width << endl;

    vector<int> kernelWidths{5, 11, 21, 61};
    auto n = kernelWidths.size();

    Mat initMat{img.size(), img.type()};

    vector<Mat> resultBlur{ makeImages( n, img.size(), img.type() ) };
    vector<Mat> resultGaussian{ makeImages( n, img.size(), img.type() ) };
    vector<Mat> resultMedian{ makeImages( n, img.size(), img.type() ) };
    vector<Mat> resultBilateral{ makeImages( n, img.size(), img.type() ) };
    

    for (size_t i = 0; i < kernelWidths.size(); ++i) {
        auto kernelWidth = kernelWidths[i];
        cv::blur(img, resultBlur[i], Size(kernelWidth, kernelWidth), Point(-1,-1));
        cv::GaussianBlur(img, resultGaussian[i], Size( kernelWidth, kernelWidth), 0,0);
        cv::medianBlur(img, resultMedian[i], kernelWidth);
        cv::bilateralFilter(img, resultBilateral[i], kernelWidth, kernelWidth*2, kernelWidth/2);
    }

    auto outBlur      = utils::concat( resultBlur, 0);
    auto outGaussian  = utils::concat( resultGaussian, 0);
    auto outMedian    = utils::concat( resultMedian, 0);
    auto outBilateral = utils::concat( resultBilateral, 0);

    cv::imwrite("./data/blurResult.png", outBlur);
    cv::imwrite("./data/gaussianBluredResult.png", outGaussian);
    cv::imwrite("./data/medianBluredResult.png", outMedian);
    cv::imwrite("./data/bilateralFilteredResult.png", outBilateral);

    cout << "finished" << endl;
    return 0;
}
} // end of namespace
