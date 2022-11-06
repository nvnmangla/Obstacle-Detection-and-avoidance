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
// /**
//  * @brief pointer to left and 
//  *        right image in a pair Image set
//  */
// struct Pair{
//   Image left;
//   Image right;
//   public:
//     Pair(cv::Mat &img1,cv::Mat &img2){
//         Image im1(img1);
//         Image im2(img2);
//         this->left = im1;
//         this->right = im2;
//     }

// };


class Image_set{

  private:  
    
    /**
     * @brief Path to calibration matrices 
     */
    string calib_path; //=  "../../data/calib";
    string left_img_dir; //=  "../../../left/*.pgm";
    string right_img_dir; //=  "../../../right/*.pgm";
    
    cv::Mat mx1; // Mapping param for left image
    cv::Mat my1;
    cv::Mat mx2; // Mapping param for right image
    cv::Mat my2;
    cv::Mat Q; //= get_qmat();// Q matrix 
  
  public:
    std::vector<cv::Mat> img_l_set; // = read_frames()[0];
    std::vector<cv::Mat> img_r_set;  // = read_frames()[1];

    // constructor 

    
  Image_set(string*, string*,string*);
      
    

    /**
     * @brief read xml files mx1,my1 ... 
     * 
     * @return vector<cv::Mat*> vector of pointers to maps  
     */
    std::vector<cv::Mat*> read_xml();
       
    std::vector<std::vector<cv::Mat>>read_frames();
    
    /**
     * @brief Get the disparity for distance 
     * 
     * @param distance at which you need dispariy (m)
     * @param infdisp // TODO need to figure out 
     * @return int disparity
     */
    int get_disparity_for_distance(double,int* );

    /**
     * @brief Construct a new vector<Image set>image set object
     * @return vector of image pair left and right
     */
    // std::vector<Pair<Image>>img_pair_set; // = get_image_pair_set();
// 
    // void get_image_pair_set();


    std::vector<cv::Mat*>  maps; // = read_xml();  

};


#endif  // IMG_SET_HPP_
