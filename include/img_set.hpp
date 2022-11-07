/**
 * @file img_set.hpp
 * @author Naveen Mangla (nmangla@umd.edu)
 * @brief  Class to modify image_sets
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IMG_SET_HPP_
#define IMG_SET_HPP_
#include<image.hpp>

class Image_set{

  private:  
    
    string calib_path; // Calibration Info Dir  
    string left_img_dir; // Left Frame 
    string right_img_dir;  // Right Frame 
    
    cv::Mat mx1; // Mapping param for left image
    cv::Mat my1;
    cv::Mat mx2; // Mapping param for right image
    cv::Mat my2;
    cv::Mat Q; // Q Matrix 
  
  public:
    std::vector<cv::Mat> img_l_set; // Set of left Frames 
    std::vector<cv::Mat> img_r_set;  // Set of Right Frames 

  // Contructor   
    Image_set(string*, string*,string*);
        
    // Reading XML files   
    std::vector<cv::Mat*> read_xml();
        
    // Reading Frames into CV::Mat 
    std::vector<std::vector<cv::Mat>>read_frames();
    
    // Getting Disparity for given distance 
    int get_disparity_for_distance(double,int* );


    // all the matrices are saved here 
    std::vector<cv::Mat*>  maps; 

};


#endif  // IMG_SET_HPP_
