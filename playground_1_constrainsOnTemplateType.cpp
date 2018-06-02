

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

struct Blue{};
struct Green{};
struct Red{};

// overload operator<< for the colors
ostream& operator<< (ostream& os, const Blue& blue)   { os << "blue"  << flush; return os; }
ostream& operator<< (ostream& os, const Green& green) { os << "green" << flush; return os; }
ostream& operator<< (ostream& os, const Red& red)     { os << "red"   << flush; return os; }
  
  
template< typename Iterator >
void print1( typename std::enable_if< std::is_same< typename std::iterator_traits<Iterator>::value_type, Blue >::value, Iterator>::type begin,
             typename std::enable_if< std::is_same< typename std::iterator_traits<Iterator>::value_type, Blue >::value, Iterator>::type end) {
    while (begin != end) {
        cout << *begin << endl;
        ++begin;
    }
}


template< typename Iterator >
using GreenIterator = typename std::enable_if< std::is_same< typename std::iterator_traits<Iterator>::value_type, Green >::value, Iterator>::type;

template< typename Iterator >
void print2( GreenIterator<Iterator> begin, GreenIterator<Iterator> end) {
    while (begin != end) {
        cout << *begin << endl;
        ++begin;
    }
}
  
  
template< typename Iterator >
using ColorIterator = typename std::enable_if< std::is_same< typename std::iterator_traits<Iterator>::value_type, Blue >::value + \
                                               std::is_same< typename std::iterator_traits<Iterator>::value_type, Green >::value, \
                                               Iterator>::type;

template< typename Iterator >
void print3( ColorIterator<Iterator> begin, ColorIterator<Iterator> end) {
    while (begin != end) {
        cout << *begin << endl;
        ++begin;
    }
}



int main() {
    // create vectors of different colors
    vector<Blue>  blues{3};
    vector<Red>   reds{3};
    vector<Green> greens{3};

    cout << "print blues: " << endl;
    print1<vector<Blue>::iterator>(blues.begin(), blues.end());
    cout << endl;
    //print1<vector<Red>::iterator>(reds.begin(), reds.end()); // error! cannot compile.

    cout << "print greens: " << endl;
    print2<vector<Green>::iterator>(greens.begin(), greens.end());
    cout << endl;

    cout << "print blues or greens: " << endl;
    print3<vector<Blue>::iterator>(blues.begin(), blues.end());
    print3<vector<Green>::iterator>(greens.begin(), greens.end());

    cout << "finished" << endl;
    return 0;
}

} // end of namespace
