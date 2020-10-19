// Copyright Non!
// Author: Jeppe Dreyer Matzen
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <math.h>
#include "myOpenCVFunctions.h"

int main()
{ 
  
    int type = 0; // 0 (grayscale), 1 (color), -1 (unchanged)
    cv::Mat img1, img2;
    std::string namefile1 = "Your_xray.png";
    myOpencvFucntions image(&img1, &type, namefile1);

    image.showImage(&img1, "Original");
    image.otsuThredshold(&img1);
    image.showImage(&img1, "Otsu");

}
