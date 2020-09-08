#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>



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
    int cout = 0, nSize = 256;
    cv::Mat image;
    cv::Mat bins = cv::Mat::zeros(nSize,nSize, CV_8UC1 ); 
    float histogramBinCount[256] = {0}; // Lav array til at have count i 

    image = cv::imread("./sample.jpg", cv::IMREAD_GRAYSCALE); //  for at få grayscale image
    // Count each bin for the histogram
  for (int i = 0; i<image.rows; i++)
  {
      for (int j = 0; j<image.cols; j++)
      {
         histogramBinCount[image.at<uchar>(i,j)]++; // Vælg < > efter type af billede, grayscale: 8 bit (ex uint8_t) 
     /* 
        Farve: <Vec3d> så den ved der er tre kanaler
        Her til går den kun den første pixel (blå) RGB er omvendt i openCV så den hedder BGR
        image.at<uint8_t>(i,j)[0] // tilgår blå
        image.at<uint8_t>(i,j)[1] // tilgår grøn
        image.at<uint8_t>(i,j)[2] // tilgår rød
     */
      };
  }
  /*Find max value*/
    float maxP = 0;
    for (int i = 0; i<nSize;i++)
    {
        if(maxP<histogramBinCount[i]) // gemmer max værdi i maxP
            maxP=histogramBinCount[i];
    }
    nSize = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));
    // Print array 
    for(int i = 0; i < nSize; i++){
       std::cout << i << ":    " << histogramBinCount[i] << std::endl;
    }

    // Normalise
    for(int i = 0; i < nSize; i++)
    {
       int normalizedHeightOfBin = cvRound(histogramBinCount[i]*nSize/maxP);
       cv::line
            (
           bins, 
           cv::Point(i, nSize-normalizedHeightOfBin), cv::Point(i, nSize), 
           cv::Scalar::all(255)
           );
    }
        std::cout << "n " << nSize << "  normalized " << maxP << std::endl;
    cv::imshow("name", bins);
    cv::imshow("hest", image);
    cv::waitKey();
  return 0;

}



