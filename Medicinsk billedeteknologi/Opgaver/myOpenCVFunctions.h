#ifndef myOpencvFucntions_H
#define myOpencvFucntions_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <string>
#include <vector>

class myOpencvFucntions
{
    public:
        myOpencvFucntions(cv::Mat *img, int *type, std::string nameOfFile);
        void showImage(cv::Mat *image, std::string name);
        void calHistogram(cv::Mat *image, std::string name);
        int getCols(cv::Mat *image);
        int getRows(cv::Mat *image);
        void filter(cv::Mat *imageIn, float *k, cv::Mat *imageOut, cv::Mat *kernal);
        void zeroPadding(cv::Mat *image, float *k, cv::Mat *paddedImage);
        void binarthredsholdedImage(cv::Mat *image, int tredsholdValue);
        void connectedComponentsAnalysisFour(cv::Mat *thresholdImage);
        void connectedComponentsAnalysisRecursion(cv::Mat *thresholdImage);
        void erodeDilate(cv::Mat *thresholdImage);
        void RCC(cv::Mat *thresholdImage, int i, int j, int label);
        void invaterGrayImage(cv::Mat *image);
        void stretchHistogram(cv::Mat *image);

    
    
    private:
    int windowSize = 700;
    
    

    
};


#endif