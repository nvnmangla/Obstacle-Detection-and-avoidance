


#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include <vector>

using std::cout;
using std::string;




#define USE_SAFTEY_CHECKS 0
#define INVARIANCE_CHECK_VERT_OFFSET_MIN (-8)
#define INVARIANCE_CHECK_VERT_OFFSET_MAX 8
#define INVARIANCE_CHECK_VERT_OFFSET_INCREMENT 2
#define INVARIANCE_CHECK_HORZ_OFFSET_MIN (-3)
#define INVARIANCE_CHECK_HORZ_OFFSET_MAX 3
#define NUMERIC_CONST 333

class Image{

    private:
        cv::Mat rgb;

    public:
        Image() = default;
        Image(cv::Mat *img);
        cv::Mat edges = get_edges();
        
        // grayscale = rgb if rgb has  < 3 channels 
        cv::Mat grayscale = get_grayscale();
        
        cv::Mat get_grayscale();
        cv::Mat get_edges();        
};


#endif  // IMAGE_HPP_