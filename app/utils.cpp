

#include <image.hpp>
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