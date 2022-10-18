#include<img_set.hpp>



std::vector<cv::Mat*> Images::read_xml(){
    cv::FileStorage fs_mx1(calib_path+"/mx1.xml",0);
    cv::FileStorage fs_my1(calib_path+"/my1.xml",0);
    cv::FileStorage fs_mx2(calib_path+"/mx2.xml",0);
    cv::FileStorage fs_my2(calib_path+"/my2.xml",0);
    cv::FileStorage fs_Q(calib_path+"/Q.xml",0);



	// building cv::mat out of xmls
	fs_mx1["mx1"] >> mx1;
	fs_my1["my1"] >> my1;
	fs_mx2["mx2"] >> mx2;
	fs_my2["my2"] >> my2;
	fs_Q["Q"] >> Q;

    fs_mx1.release();
    fs_my1.release();
    fs_mx2.release();
    fs_my2.release();
    fs_Q.release();



    std::vector<cv::Mat*> maps = {&mx1,&my1,&mx2,&my2,&Q};
    return maps;
}


std::vector<std::vector<cv::Mat>> Images::read_frames(){

    std::vector<std::vector<cv::Mat>> frames;
    std::vector<std::string>fn_r, fn_l;
    std::vector<cv::Mat>image_l_set,image_r_set;
    
    cv::glob(left_img_dir,fn_l);
    cv::glob(right_img_dir,fn_r);
    
    
    int count = (fn_r.size()); 

    for (int i{}; i<count; i++){

        cv::Mat imagel =  cv::imread(fn_l[i],0);
        cv::Mat imager =  cv::imread(fn_r[i],0);

        image_l_set.push_back(imagel);
        image_r_set.push_back(imager);

        }

    frames.push_back(image_l_set);
    frames.push_back(image_r_set);

    
    return frames;   
    
}



//TODO Read and comment this 
int Images::get_disparity_for_distance(double distance,int *infdisp){ 
    int min_search = -100;
    int max_search = 100;

    std::vector<cv::Point3f> disparity_candidates;
    std::vector<int> disparity_values;
    for (int i = min_search; i <= max_search; i++) {
        disparity_candidates.push_back(cv::Point3f(0, 0, -i)); 
        disparity_values.push_back(i);
    }
    std::vector<cv::Point3f> vector_3d_out;

    cv::perspectiveTransform(disparity_candidates, vector_3d_out,Q);

    int best_disparity = 0;
    double best_dist_abs = -1;
    double max_dist = -1000;
    int max_disparity = 0;

    for (int i{}; i < static_cast<int>(vector_3d_out.size()); i++) {
        double this_dist_abs = fabs(vector_3d_out.at(i).z - distance);
        
        if (best_dist_abs == -1 || this_dist_abs < best_dist_abs) {
            best_disparity = disparity_values.at(i);
            best_dist_abs = this_dist_abs;
        }

        if (vector_3d_out.at(i).z > max_dist) {
            max_dist = vector_3d_out.at(i).z;
            max_disparity = disparity_values.at(i);
        }
    }

    if (infdisp != nullptr) {
        *infdisp = max_disparity;
    }

    return best_disparity;

}

std::vector<Image_set>Images::get_image_pair_set(){

    std::vector<Image_set>img_set;

    for(int i{};i<static_cast<int>(img_l_set.size());i++){


            Image_set img_pair;
            img_pair.left = img_l_set[i];
            img_pair.right = img_r_set[i];

            img_set.push_back(img_pair);
    }
    return img_set;
}