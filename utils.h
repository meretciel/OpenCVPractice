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
    cv::Mat concat(const std::vector<cv::Mat>& matVec, int axis=0);

}

#endif /* UTILS_H_ */
