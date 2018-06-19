/*
 * Cell.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: Ruikun
 */

#include "Cell.h"
#include <stdexcept>
#include <iostream>

using cv::Point;
using cv::Mat;
using cv::Scalar;
using std::string;
using std::cout;
using std::endl;

Cell::Cell(Point topLeft, Point bottomRight): _topLeft{topLeft}, _bottomRight{bottomRight} {};
Cell::Cell(Point topLeft, int width, int height): Cell( topLeft, Point(topLeft.x+width, topLeft.y + height) ) {};

void Cell::addFrame( Mat& img, Scalar color, int thickness ) {
    _frameThickness = thickness;
    _frameColor     = color;
    rectangle( img, _topLeft, _bottomRight, color, thickness);
}

void Cell::fill( Mat& img, Scalar color ) {
    _filledColor = color;
    rectangle(img, _topLeft, _bottomRight, color, CV_FILLED);
}


void Cell::reAddFrame( cv::Mat& img ) { addFrame(img, frameColor(), frameThickness()); }
void Cell::reFill( cv::Mat& img ) { fill(img, filledColor()); }

void Cell::addText( Mat& img, string text, Scalar color, double xratio, double yratio,double scale, int thickness ) {
    int x = _topLeft.x + (_bottomRight.x - _topLeft.x) * xratio;
    int y = _bottomRight.y - (_bottomRight.y - _topLeft.y) * yratio;
    Point origin{ x, y};
    putText( img, text, origin, cv::FONT_HERSHEY_COMPLEX_SMALL, scale, color, thickness, cv::LINE_8 );
}

void Cell::clearText( cv::Mat& img ) {
    reFill(img);
    reAddFrame(img);
}


std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, const std::vector<int>& width, const std::vector<int>& height) {
    int N = width.size();
    if (height.size() != N) throw std::invalid_argument( "width and height have different size.");

    int x = origin.x;
    int y = origin.y;
    std::vector<Cell> output;

    if ( direction == Direction::posX ) {
        for (int i = 0; i < N; ++i) {
            Point p1{ x, y };
            Point p2{ x + width[i], y + height[i] };
            output.push_back( Cell{p1, p2} );
            x += width[i];
        }
    }
    else if ( direction == Direction::posY ) {
        for (int i = 0; i < N; ++i) {
            Point p1{ x, y };
            Point p2{ x + width[i], y + height[i] };
            output.push_back( Cell{p1, p2} );
            y += height[i];
        }
    }
    else if ( direction == Direction::negY ) {
        for (int i = 0; i < N; ++i) {
            y -= height[i];
            Point p1{ x, y };
            Point p2{ x + width[i], y + height[i] };
            output.push_back( Cell{p1, p2} );
        }
    }

    return output;
}


std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, int width, const std::vector<int>& height) {
    auto N = height.size();
    return makeCells1D( origin, direction, std::vector<int>(N, width), height);
}

std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, const std::vector<int>& width, int height) {
    auto N = width.size();
    return makeCells1D( origin, direction, width, std::vector<int>(N,height) );
}

std::vector<Cell> makeCells1D( cv::Point origin, Direction direction, int width, int height, int N ) {
    return makeCells1D( origin, direction, std::vector<int>(N, width), std::vector<int>(N, height) );
}
