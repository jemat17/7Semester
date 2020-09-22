#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include "myOpenCVFunctions.h"




/* Big O (n^3)
Load image as Matrix (image.size[0] X image.size[1])

int histogramBins[256] = 0; // Lav array til at 

find image row and cols

    for(j = 0; j < image.size[0]; j++){
        for(k = 0; k < image.size[1]; k++){
            histogramBins(image.at<uchar>(j, k)++;
        }
    }

Evt normalisere (værdierne i histogramBins må ikke være int)

tegn histogrammet med værdierne fra arr

*/

int main()
{
    int cout = 0;
    float rangeOfPixels = 256, windowSize = 700;

    int histogram1[256] = {0};

    cv::Mat image;
    cv::Mat bins = cv::Mat::zeros(windowSize,windowSize, CV_8UC1 ); // hvorfor? 256*256
    int histogramBinCount[256] = {0}; // Lav array til at have count i 

    image = cv::imread("./hest.jpg", cv::IMREAD_GRAYSCALE); //  for at få grayscale image


  /*Find max value*/
    float maxP = image.rows * image.cols;

    rangeOfPixels = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));
    // Print array 
    for(int i = 0; i < rangeOfPixels; i++){
       //std::cout << i << ":    " << histogramBinCount[i] << std::endl;
    }
    float sum = 0;
    // Normalise
    for(int i = 0; i < rangeOfPixels; i++)
    {
       float normalizedHeightOfBin = histogramBinCount[i]/maxP; //hvorfor normalisere vi med MAX?
       std::cout << i << ":    " << normalizedHeightOfBin << std::endl;
     
       sum += normalizedHeightOfBin;
       cv::line
            (
           bins, 
           cv::Point(i*(windowSize/rangeOfPixels), windowSize), cv::Point(i*(windowSize/rangeOfPixels), windowSize-normalizedHeightOfBin), // gange 100 for procent
           cv::Scalar::all(255) //hvid farve
           );
    }
    cv::imshow("name", bins);
    cv::imshow("hest", image);
    cv::waitKey();
  return 0;    
}



