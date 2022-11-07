/**
 * @file utils.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTILS_HPP_
#define UTILS_HPP_
int GetSAD(std::vector<Image> img, int blockize, int disparity, int sobelLimit,int pxX, int pxY) ;

bool CheckHorizontalInvariance(std::vector<Image> img, int j, int i,int blockize,int disparity,int sobellimit,float threshhold);
#endif
