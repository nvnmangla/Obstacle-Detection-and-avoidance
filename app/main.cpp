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

int main() {
  // Various  Directories
  string left_dir = "../../../left/*.pgm";
  string right_dir = "../../../right/*.pgm";
  string calib_path = "../../data/calib";

  
    int blockize = 5;
    int disparity = GetDisparityForDistance(20,&infdisp);
    int threshhold =54;
    int sobellimit =10;
  
  
  Image_set img_set(&left_dir, &right_dir, &calib_path);

  for (int i{}; i < (int)img_set.img_l_set.size(); i++) {
    Image left(img_set.img_l_set[i]);
    Image right(img_set.img_r_set[i]);

    std::vector<Image> img{left, right};
    cv::imshow("name2",img[0].edge);

    img[0].threshold();
    img[1].threshold();

    cv::imshow("name1",img[0].edge);
    cv::waitKey(10);

    int startJ = 0;
    int stopJ = img[0].grayscale.cols - (disparity + blockize);

  }

  return 0;
}