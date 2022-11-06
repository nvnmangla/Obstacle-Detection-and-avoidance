#include <img_set.hpp>

int main(){
    string left_dir = "../../../left/*.pgm";
    string right_dir = "../../../right/*.pgm";
    string calib_path = "../../data/calib";
    

    //Creating image object
    Image_set img_set(&left_dir,&right_dir,&calib_path);


    cout<<img_set.img_l_set[1].size()<<"\n";
    auto q = *img_set.maps[4];
    cout<<q.rows;

    for(int i{};i<img_set.img_l_set.size();i++){

        // cv::imshow("Named Window",img_set.img_l_set[i]);

        Image left(img_set.img_l_set[i]);
        Image right(img_set.img_r_set[i]);
        cv::imshow("Named window",left.edge);
        cv::waitKey(1);

    }
    // auto img_pairs = img_set.img_pair_set;

    // cv::imshow("frame left",img_pairs[2400].left);
    // cv::imshow("frame right",img_pairs[2400].right);

    // cv::waitKey(0);



    return 0;
}