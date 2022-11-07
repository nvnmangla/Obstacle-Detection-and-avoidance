

#include <image.hpp>
#include<utils.hpp>

#include <img_set.hpp>

int GetSAD(std::vector<Image> img, int blockize, int disparity, int sobelLimit,
           int pxX, int pxY) {
  using namespace cv;

  int startX = pxX;
  int startY = pxY;

  int endX = pxX + blockize - 1;
  int endY = pxY + blockize - 1;

  int leftVal = 0, rightVal = 0, sad = 0;

  for (int i = startY; i <= endY; i++) {
    for (int j = startX; j <= endX; j++) {
      uchar sL = img[0].edge.at<uchar>(i, j);
      uchar sR = img[1].edge.at<uchar>(i, j + disparity);
      leftVal += sL;
      rightVal += sR;

      uchar pxL = img[0].grayscale.at<uchar>(i, j);
      uchar pxR = img[1].grayscale.at<uchar>(i, j + disparity);

      sad += abs(pxL - pxR);
    }
  }

    int laplacian_value = leftVal + rightVal;
    if (leftVal < sobelLimit || rightVal < sobelLimit)    {
        return -1;
    }
    return NUMERIC_CONST*(float)sad/(float)laplacian_value;
}


bool CheckHorizontalInvariance(std::vector<Image>img, int pxX, int pxY,int blockize,int disparity,int sobelLimit,float threshold) {
    int startX = pxX;
    int startY = pxY;
    int endX = pxX + blockize - 1;
    int endY = pxY + blockize - 1;

    if (   startX + disparity + INVARIANCE_CHECK_HORZ_OFFSET_MIN < 0
        || endX + disparity + INVARIANCE_CHECK_HORZ_OFFSET_MAX > img[1].grayscale.cols) {

        return true;
    }

    if (startY + INVARIANCE_CHECK_VERT_OFFSET_MIN < 0
        || endY + INVARIANCE_CHECK_VERT_OFFSET_MAX > img[1].grayscale.rows) {
        
        return true;

    }

    int leftVal = 0;

    int right_val_array[400];
    int sad_array[400];
    int sobel_array[400];

    for (int i=0;i<400;i++) {
        right_val_array[i] = 0;
        sad_array[i] = 0;
        sobel_array[i] = 0;
    }

    int counter = 0;

    for (int i=startY;i<=endY;i++)
    {
        for (int j=startX;j<=endX;j++)
        {
            uchar pxL = img[0].grayscale.at<uchar>(i,j);

            uchar pxR_array[400], sR_array[400];
            counter = 0;

            for (int vert_offset = INVARIANCE_CHECK_VERT_OFFSET_MIN;
                vert_offset <= INVARIANCE_CHECK_VERT_OFFSET_MAX;
                vert_offset+= INVARIANCE_CHECK_VERT_OFFSET_INCREMENT) {

                for (int horz_offset = INVARIANCE_CHECK_HORZ_OFFSET_MIN;
                    horz_offset <= INVARIANCE_CHECK_HORZ_OFFSET_MAX;
                    horz_offset++) {

                    pxR_array[counter] = img[1].grayscale.at<uchar>(i + vert_offset, j + disparity + horz_offset);
                    sR_array[counter] = img[1].edge.at<uchar>(i + vert_offset, j + disparity + horz_offset);
                    right_val_array[counter] += sR_array[counter];

                    sad_array[counter] += abs(pxL - pxR_array[counter]);


                    counter ++;
                }
            }

            uchar sL = img[0].edge.at<uchar>(i,j);

            leftVal += sL;

        }
    }

    for (int i = 0; i < counter; i++)
    {
        sobel_array[i] = leftVal + right_val_array[i];
        
        if (right_val_array[i] >= sobelLimit && NUMERIC_CONST*5*(float)sad_array[i]/((float)sobel_array[i]) < threshold) {
            return true;
        }
    }
    return false;


}
