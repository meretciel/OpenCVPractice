
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

Mat helper( const Mat& img, int op, int N, const vector<Mat>& kernels, const vector<string>& captions ) {
    auto mats = makeImages( N, img.size(), img.type() );
    vector<Mat> output{img};

    for (int k = 0; k < N; ++k) {
        auto kernel = kernels[k];
        cv::morphologyEx( img, mats[k], op, kernel);
        output.push_back( mats[k] );
    }

    for (int k = 0; k < N+1; ++k) {
        output[k] = utils::addCaption( output[k], captions[k], 40, 0.35, 0.57 );
    }

    return utils::concat( output, 0, 0.2 );
}


int main() {
    string filename{"./data/random_binary_5.png"};
    Mat img = imread( filename, cv::IMREAD_GRAYSCALE );

    vector<Size> sizes{ Size{3,3}, Size{10,10} };
    vector<Mat> kernels;
    for (auto& size : sizes) { kernels.push_back( cv::getStructuringElement( cv::MorphShapes::MORPH_RECT, size ) ); }

    auto imgErosion  = helper( img, cv::MorphTypes::MORPH_ERODE,    2, kernels, {"Original", "Erosion 3*3",  "Erosion 10*10"} );
    auto imgDilation = helper( img, cv::MorphTypes::MORPH_DILATE,   2, kernels, {"Original", "Dilation 3*3", "Dilation 10*10"} );
    auto imgOpen     = helper( img, cv::MorphTypes::MORPH_OPEN,     2, kernels, {"Original", "Open 3*3",     "Open 10*10"} );
    auto imgClose    = helper( img, cv::MorphTypes::MORPH_CLOSE,    2, kernels, {"Original", "Close 3*3",    "Close 10*10"} );
    auto imgGradient = helper( img, cv::MorphTypes::MORPH_GRADIENT, 2, kernels, {"Original", "Gradient 3*3", "Gradient 10*10"} );

    cv::imwrite("./data/morph_erosion.png", imgErosion);
    cv::imwrite("./data/morph_dilation.png", imgDilation);
    cv::imwrite("./data/morph_open.png", imgOpen);
    cv::imwrite("./data/morph_close.png", imgClose);
    cv::imwrite("./data/morph_gradient.png", imgGradient);

    cout << "finished." << endl;

    return 0;
}

} // end of namespace


