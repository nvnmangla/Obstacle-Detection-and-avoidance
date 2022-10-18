#include <img_set.hpp>

int main(){
    string left_dir = "../../data/left/*.pgm";
    string right_dir = "../../data/*.pgm";
    

    //Creating image object
    Images img_set;


    cout<<img_set.img_l_set[1].size()<<"\n";
    auto q = *img_set.maps[4];
    cout<<q.rows;


    auto img_pairs = img_set.img_pair_set;

    cv::imshow("frame left",img_pairs[2400].left);
    cv::imshow("frame right",img_pairs[2400].right);

    cv::waitKey(0);



    return 0;
}