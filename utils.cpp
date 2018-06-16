/*
 * utils.cpp
 *
 *  Created on: May 25, 2018
 *      Author: ruikun
 */



#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "utils.h"
#include <cmath>
#include <stdexcept>

using std::string;
using cv::Size;
using cv::Scalar;
using cv::Mat;
using cv::Point;

using namespace std;


std::string utils::getTypeName( int x ) {
    switch (x) {
        case CV_8UC1:  return "CV_8UC1";
        case CV_8UC2:  return "CV_8UC2";
        case CV_8UC3:  return "CV_8UC3";
        case CV_8UC4:  return "CV_8UC4";
        case CV_8SC1:  return "CV_8SC1";
        case CV_8SC2:  return "CV_8SC2";
        case CV_8SC3:  return "CV_8SC3";
        case CV_8SC4:  return "CV_8SC4";
        case CV_16UC1: return "CV_16UC1";
        case CV_16UC2: return "CV_16UC2";
        case CV_16UC3: return "CV_16UC3";
        case CV_16UC4: return "CV_16UC4";
        case CV_16SC1: return "CV_16SC1";
        case CV_16SC2: return "CV_16SC2";
        case CV_16SC3: return "CV_16SC3";
        case CV_16SC4: return "CV_16SC4";
        case CV_32SC1: return "CV_32SC1";
        case CV_32SC2: return "CV_32SC2";
        case CV_32SC3: return "CV_32SC3";
        case CV_32SC4: return "CV_32SC4";
        case CV_32FC1: return "CV_32FC1";
        case CV_32FC2: return "CV_32FC2";
        case CV_32FC3: return "CV_32FC3";
        case CV_32FC4: return "CV_32FC4";
        case CV_64FC1: return "CV_64FC1";
        case CV_64FC2: return "CV_64FC2";
        case CV_64FC3: return "CV_64FC3";
        case CV_64FC4: return "CV_64FC4";
        default: return "Unknown type: " + std::to_string(x);
    }

}


cv::Mat utils::concat(const std::vector<cv::Mat>& matVec, int axis, double sepRatio, Scalar sepColor){
    if (matVec.size() == 0) {return Mat{};}

    if ( sepRatio < 0 ) { throw std::invalid_argument("sepRatio cannot be negative."); }

    vector<Mat> matVecWithSep;

    if (sepRatio > 0.0001) {
        int totalWidth = 0;
        for (const auto& item : matVec ) { totalWidth += item.size().width; }
        int width =  totalWidth / double( matVec.size() ) * sepRatio;

        Mat prev;
        for (const auto& mat : matVec) {
            if (!prev.empty()) { matVecWithSep.push_back( Mat{ Size{ width, prev.size().height }, prev.type(), sepColor } ); }
            matVecWithSep.push_back( mat );
            prev = mat;
        }
    }
    else {
        matVecWithSep = matVec;
    }


    if (axis == 0) {
        int totalWidth = 0;
        int height = -1;

        for (const auto& mat : matVecWithSep) {
            if (height == -1) {
                height = mat.size().height;
            }
            else if (mat.size().height != height) {
                throw std::runtime_error("Images have different height.");
            }
            totalWidth += mat.size().width;
        }

        cv::Mat outImg{cv::Size(totalWidth, height), matVecWithSep[0].type()};

        int x = 0;
        for (const auto& mat : matVecWithSep) {
            auto width = mat.size().width;
            cv::Rect roi{x,0,width, height};
            mat.copyTo( outImg(roi) );
            x += width;
        }
        return outImg;
    }
    else {
        int totalHeight = 0;
        int width = -1;

        for (const auto& mat : matVecWithSep) {
            if (width == -1) {
                width = mat.size().width;
            }
            else if (mat.size().width != width) {
                throw std::runtime_error("Images have different width.");
            }
            totalHeight += mat.size().height;
        }

        cv::Mat outImg{cv::Size(width, totalHeight), matVecWithSep[0].type()};

        int y = 0;
        for (const auto& mat : matVecWithSep) {
            auto height = mat.size().height;
            cv::Rect roi{0, y, width, height};
            mat.copyTo( outImg(roi) );
            y += height;
        }
        return outImg;
    }
}




Mat utils::addCaption( const Mat& img, const string& text, int height, double xRatio, double yRatio, double scale, Scalar color,int thickness, const string pos ) {

    auto width = img.size().width;

    // create caption part of the output image
    Mat imgCaption{ Size{ width, height }, img.type(), Scalar{255,255,255,255} };

    int x = width * xRatio;
    int y = height * yRatio;
    Point origin{ x, y };

    putText( imgCaption, text, origin, cv::FONT_HERSHEY_COMPLEX_SMALL, scale, color, thickness, cv::LINE_8 );

    if ( pos == "bottom" ) {
        return utils::concat( { img, imgCaption }, 1 );
    }
    else {
        return utils::concat( { imgCaption, img }, 0 );
    }

}
