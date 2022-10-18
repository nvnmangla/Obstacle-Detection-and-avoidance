/**
 * @file image.cpp
 * @author Naveen Mangla(nmangla@umd.edu)
 * @brief Image class function definations
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<image.hpp>
#include<img_set.hpp>


cv::Mat Image::get_grayscale(){

    cv::Mat gray;
    if (rgb.channels()<3){
        return rgb;}
    else {cv::cvtColor(rgb, gray,cv::COLOR_BGR2BGRA);};
    return gray;

}

cv::Mat Image::get_edges(){

    cv::Mat lap;
    cv::Laplacian(grayscale,lap,-1, 3, 1, 0,cv::BORDER_DEFAULT );
    return lap;
}

Image::Image(cv::Mat *img){
    this->rgb = *img;
}
