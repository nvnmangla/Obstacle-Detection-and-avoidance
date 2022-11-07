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

#include <img_set.hpp>

cv::Mat Image::get_grayscale() {
  cv::Mat gray;
  if (this->rgb.channels() < 3) {
    gray = this->rgb;
  } else {
    cv::cvtColor(rgb, gray, cv::COLOR_BGR2BGRA);
  };
  return gray;
}

cv::Mat Image::get_edges() {
  cv::Mat lap;
  cv::Laplacian(this->grayscale, lap, -1, 3, 1, 0, cv::BORDER_DEFAULT);
  return lap;
}

Image::Image(cv::Mat img) {
  this->rgb = img;
  this->grayscale = this->get_grayscale();
  this->edge = this->get_edges();
}

void Image::threshold() {
  cv::threshold(this->edge, this->edge, this->threshvalue, 255, 3);
}
