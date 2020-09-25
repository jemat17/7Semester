#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <math.h>
#include "myOpenCVFunctions.h"




/* 
Padding!
    zeroes der er Imgage[rows+2, cols+2]
    for for
        image[1,1] = imageOG[0,0] til image [end-1, end-1] = imageOG[end,end]

Filter:
        for
         for til at læse matrix
            fra image[1,1] til image[end-1, end-1]
                Forloop til at finde sum af 3X3
                sum = -..... * 1/9

cv::CV_assert
        
*/
int main()
{
    cv::Mat img1; 
    float padding = 3;
    cv::Mat kernal = cv::Mat::ones( padding, padding, CV_8UC1 );
    int type = 0; // 0 (grayscale), 1 (color), -1 (unchanged)
    

    myOpencvFucntions image(&img1, &type);

    cv::Mat paddedImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1), image.getCols(&img1) + (padding-1), CV_8UC1 );
    cv::Mat filteredImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1),  image.getCols(&img1) + (padding-1), CV_8UC1 );
    cv::Mat thresholdImage = cv::Mat::zeros(paddedImage.rows, paddedImage.cols, CV_8UC1 );

    image.zeroPadding(&img1, &padding, &paddedImage);
    
    image.connectedComponentsAnalysisFour(&paddedImage);

    //image.binarthredsholdedImage(&paddedImage);
    //image.connectedComponentsAnalysisRecursion(&paddedImage);

    //image.filter(&paddedImage, &padding, &filteredImage, &kernal);  
    cv::namedWindow("img1", cv::WINDOW_AUTOSIZE); 
    cv::imshow("img1", img1); // Show window 
    cv::namedWindow("connectedComponentsAnalysisRecursion1", cv::WINDOW_AUTOSIZE); 
    cv::imshow("connectedComponentsAnalysisRecursion1", filteredImage); // Show window 
    
    cv::waitKey(0);

    return 0;

}