#ifndef myOpencvFucntions_H
#define myOpencvFucntions_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <string>

class myOpencvFucntions
{
    public:
        myOpencvFucntions(cv::Mat *img, int *type);
        void calHistogram(cv::Mat *image);
        void showHistogram();
        int getCols(cv::Mat *image);
        int getRows(cv::Mat *image);
        //void filter(cv::Mat *imageIn, float *k, cv::Mat *imageOut, int weighted[3][3]);
        void zeroPadding(cv::Mat *image, float *k, cv::Mat *paddedImage);
        void thredsholdedImage(cv::Mat *image);
        void connectedComponentsAnalysisFour(cv::Mat *thresholdImage);

    
    
    private:
    int rangeOfPixels = 256, windowSize = 700;
    float histogramBinCount[256] = {0};
    cv::Mat bins = cv::Mat::zeros(windowSize,windowSize, CV_8UC1 );

    
};


#endif