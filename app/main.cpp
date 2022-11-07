/**
 * @file main.cpp
 * @author Naveen Mangla (nmangla@umd.edu)
 * @brief
 * @version 0.1
 * @date 2022-11-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <img_set.hpp>
#include <utils.hpp>

int main() {
  // Various  Directories
  string left_dir = "../../../left/*.pgm";
  string right_dir = "../../../right/*.pgm";
  string calib_path = "../../data/calib";

  int blockize = 5;
  int threshhold = 54;
  int sobellimit = 10;
  int infdisp;

  Image_set img_set(&left_dir, &right_dir, &calib_path);

  int disparity = img_set.get_disparity_for_distance(20, &infdisp);

  for (int i{}; i < (int)img_set.img_l_set.size(); i++) {
    Image left(img_set.img_l_set[i]);
    Image right(img_set.img_r_set[i]);

    std::vector<Image> img{left, right};
    cv::Mat dekh;
    cv::cvtColor(img[0].grayscale, dekh, cv::COLOR_GRAY2BGR);

    img[0].threshold();
    img[1].threshold();


    int startJ = 0;
    int stopJ = img[0].grayscale.cols - (disparity + blockize);

    if (disparity < 0) {
      startJ = -disparity;
      stopJ = img[0].grayscale.cols - blockize;
    }

    int hitCounter = 0;

    int row_start = 0;
    int row_end = img[0].grayscale.rows - blockize;

    for (int i = row_start; i < row_end; i += blockize) {
      for (int j = startJ; j < stopJ; j += blockize) {
        int sad = GetSAD(img, blockize, disparity, sobellimit, j, i);

        if (sad < threshhold && sad >= 0) {
          if (CheckHorizontalInvariance(img, j, i, blockize, disparity,
                                        sobellimit, threshhold) == false) {
            

            uchar pxL = img[0].grayscale.at<uchar>(i, j);

            cv::circle(dekh, cv::Point(j, i), 2, cv::Scalar(0, 0, 255), -1);

            hitCounter++;
          }
        }
      }
    }
    cv::imshow("Obstacles",dekh);
    cv::waitKey(10);
  }

  return 0;
}