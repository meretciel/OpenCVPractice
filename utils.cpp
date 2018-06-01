/*
 * utils.cpp
 *
 *  Created on: May 25, 2018
 *      Author: ruikun
 */



#include <iostream>
#include "utils.h"


using cv::Size;
using cv::Scalar;
using cv::Mat;


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


cv::Mat utils::concat(const std::vector<cv::Mat>& matVec, int axis){
    if (matVec.size() == 0) {return Mat{};}

    if (axis == 0) {
        int totalWidth = 0;
        int height = -1;

        for (const auto& mat : matVec) {
            if (height == -1) {
                height = mat.size().height;
            }
            else if (mat.size().height != height) {
                throw std::runtime_error("Images have different height.");
            }
            totalWidth += mat.size().width;
        }

        cv::Mat outImg{cv::Size(totalWidth, height), matVec[0].type()};

        int x = 0;
        for (const auto& mat : matVec) {
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

        for (const auto& mat : matVec) {
            if (width == -1) {
                width = mat.size().width;
            }
            else if (mat.size().width != width) {
                throw std::runtime_error("Images have different width.");
            }
            totalHeight += mat.size().height;
        }

        cv::Mat outImg{cv::Size(width, totalHeight), matVec[0].type()};

        int y = 0;
        for (const auto& mat : matVec) {
            auto height = mat.size().height;
            cv::Rect roi{0, y, width, height};
            mat.copyTo( outImg(roi) );
            y += height;
        }
        return outImg;
    }
}
