

# include<image.hpp>
# include<img_set.hpp>

int GetSAD(Image img,int blockize,int disparity,int sobelLimit,int pxX,int pxY){
    
    using namespace cv;

    int startX = pxX;
    int startY = pxY;

    int endX = pxX + blockize - 1;
    int endY = pxY + blockize - 1;

    int leftVal = 0, rightVal = 0,sad = 0;

    for (int i=startY;i<=endY;i++) {
            for (int j=startX;j<=endX;j++) {
                uchar sL = img.left.edges.at<uchar>(i,j);
                uchar sR = img.right.edges.at<uchar>(i,j+disparity);
                leftVal += sL;
                rightVal += sR;

                uchar pxL = leftImage.at<uchar>(i,j);
                uchar pxR = rightImage.at<uchar>(i,j+disparity);

                sad += abs(pxL - pxR);
              
            }
    }
