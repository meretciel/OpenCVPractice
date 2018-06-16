/*
 * utils.h
 *
 *  Created on: May 25, 2018
 *      Author: ruikun
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdexcept>




namespace utils {

    std::string getTypeName( int x );
    cv::Mat concat(const std::vector<cv::Mat>& matVec, int axis=0, double sepRatio=0, cv::Scalar sepColor=cv::Scalar{255,255,255,255});
    cv::Mat addCaption( const cv::Mat& img, const std::string& text, int height, double xRatio, double yRatio, double scale=1,\
                        cv::Scalar color=cv::Scalar{0,0,0,255}, int thickness=1, const std::string pos="bottom" );

}

#endif /* UTILS_H_ */
