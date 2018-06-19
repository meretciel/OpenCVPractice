/*
 * Cell.h
 *
 *  Created on: Jun 18, 2018
 *      Author: Ruikun
 */

#ifndef CELL_H_
#define CELL_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Cell {
private:
    cv::Point  _topLeft{0,0};
    cv::Point  _bottomRight{0,0};
    int        _frameThickness{1};
    cv::Scalar _frameColor{255,255,255, 255};
    cv::Scalar _filledColor{255,255,255,255};

public:
    Cell() = default;
    Cell(cv::Point topLeft, cv::Point bottomRight);
    Cell(cv::Point topLeft, int width, int height);

    void addFrame( cv::Mat& img, cv::Scalar color, int thickness = 1);
    void fill( cv::Mat& img, cv::Scalar color );
    void reAddFrame( cv::Mat& img );
    void reFill( cv::Mat& img);

    void addText( cv::Mat& img, std::string text, cv::Scalar color, double xratio, double yratio, double scale = 1., int thickness = 1);
    void clearText( cv::Mat& img );

    cv::Point topLeft() const { return _topLeft; };
    cv::Point bottomRight() const { return _bottomRight; }
    cv::Scalar frameColor() const { return _frameColor; }
    cv::Scalar filledColor() const { return _filledColor; }
    int frameThickness() const { return _frameThickness; }
    int width() const { return _bottomRight.x - _topLeft.x; }
    int height() const { return _bottomRight.y - _topLeft.y; }

};


enum class Direction{ posX, posY, negY };

std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, const std::vector<int>& width, const std::vector<int>& height);
std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, int width, const std::vector<int>& height);
std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, const std::vector<int>& width, int height);
std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, int width, int height, int N );

#endif /* CELL_H_ */
