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

// 1: By using a combination of erosion and dilation on the Rice.tif image – find the contours of all the rice
    int type = 0; // 0 (grayscale), 1 (color), -1 (unchanged)
    /*cv::Mat img1, img2;
    std::string namefile1 = "rice.tif";
    myOpencvFucntions image(&img1, &type, namefile1);

    image.showImage(&img1, "Original");
    image.calHistogram(&img1, "hidt");
    image.otsuThredshold(&img1);
    
    img1.copyTo(img2);

    image.erode(&img1);


    image.showImage(&img1, "Original");

    for(int i = 0; i < image.getRows(&img1); i++) {
        for(int j = 0; j < image.getCols(&img1); j++ ) {
            img2.at<uchar>( i , j ) =  img2.at<uchar>( i , j) - img1.at<uchar>( i , j); 
        }
    }
    image.showImage(&img2, "Outline");


// 2: Using the images RoBlood_man_thres.bmp and RoBlood_MathcedFilterResult.bmp find the pixel ratio of the green over red pixels in the figure 1.
    cv::Mat img3, img4;
    
    std::string namefile3 = "RoBlood_man_thres.bmp"; 
    std::string namefile4 = "RoBlood_MathcedFilterResult.bmp";
    myOpencvFucntions image2(&img3, &type, namefile3);
    myOpencvFucntions image3(&img4, &type, namefile4);
    cv::Mat img5 = cv::Mat::zeros(image.getRows(&img3),  image.getCols(&img3), CV_8UC1 );


    // Billederne består af 0 og 255 

    // Find pixel ratio for røde pixels.
    
    float redPixel = 0;

    for(int i = 0; i < img3.rows; i++) {
        for( int j = 0; j < img3.cols; j++) {
            if(img3.at<uchar>( i , j ) == 255 ) {
                redPixel++;
            }       
        }                
    }

    // Find de grønne områder

    float greenPixel = 0;

    for(int i = 0; i < img4.rows; i++) {
        for( int j = 0; j < img4.cols; j++) {
            if(img3.at<uchar>( i , j ) == img4.at<uchar>( i , j ) && img3.at<uchar>( i , j ) == 255) {
                greenPixel++;
                img5.at<uchar>( i , j ) = 255;
            } 
            else {
                img5.at<uchar>( i , j ) = 0;
            }      
        }                
    }

    float pixelRatio = greenPixel / redPixel;

    image.showImage(&img5, "ratio");

    std::cout << "red" << redPixel << std::endl;
    std::cout << "green" << greenPixel << std::endl;
    std::cout << "frac" << pixelRatio << std::endl;
*/
    // Opgave 3:  On the US00002S.tif separate the background from the anatomical information.
    cv::Mat img6;
    std::string namefile5 = "rice.tif";
    myOpencvFucntions image4(&img6, &type, namefile5);

    image4.showImage(&img6, "Original");

    int thredsholdboxSize = 50, increment = thredsholdboxSize * 2, C = 0;
    int x1, x2, x3, x4, thredshold;

    for( int k = thredsholdboxSize; k < img6.rows; ) {
        for( int l = thredsholdboxSize; l < img6.cols; ) {
            // Check for segemtation failure:
            if( k - thredsholdboxSize >= 0 && l - thredsholdboxSize >= 0 && k + thredsholdboxSize < img6.rows && l + thredsholdboxSize < img6.cols) {            
                // Første firekant
                x1 = image4.otsuThredsholdValue(&img6, k - thredsholdboxSize, l - thredsholdboxSize, thredsholdboxSize);
                // Anden firekant
                x2 = image4.otsuThredsholdValue(&img6, k - thredsholdboxSize, l, thredsholdboxSize);
                // Tredje firekant
                x3 = image4.otsuThredsholdValue(&img6, k, l - thredsholdboxSize, thredsholdboxSize);
                // Fjerde firekant
                x4 = image4.otsuThredsholdValue(&img6, k, l, thredsholdboxSize);

                thredshold = cvRound( ((x1 + x2 + x3 + x4) / 4) - C );
                if(thredshold < 0) {
                    thredshold = C;
                }
                for(int i = k - thredsholdboxSize; i < k + thredsholdboxSize; i ++ ) {
                    for(int j = l - thredsholdboxSize; j < l + thredsholdboxSize; j++ ) {
                        if ( img6.at<uchar>( i , j ) > thredshold ) {
                            img6.at<uchar>( i , j ) = -1;
                        }
                        else {
                            img6.at<uchar>( i , j ) = 0;
                        }
                    }
                }
            }
            if( k - thredsholdboxSize >= 0 && l - thredsholdboxSize >= 0 && k + thredsholdboxSize < img6.rows && l + thredsholdboxSize > img6.cols){
                int ll = img6.cols - thredsholdboxSize;
                // Første firekant
                x1 = image4.otsuThredsholdValue(&img6, k - thredsholdboxSize, ll - thredsholdboxSize, thredsholdboxSize);
                // Anden firekant
                x2 = image4.otsuThredsholdValue(&img6, k - thredsholdboxSize, ll, thredsholdboxSize);
                // Tredje firekant
                x3 = image4.otsuThredsholdValue(&img6, k, ll - thredsholdboxSize, thredsholdboxSize);
                // Fjerde firekant
                x4 = image4.otsuThredsholdValue(&img6, k, ll, thredsholdboxSize);

                thredshold = cvRound( ((x1 + x2 + x3 + x4) / 4) - C );
                if(thredshold < 0) {
                    thredshold = C;
                }
                for(int i = k - thredsholdboxSize; i < k + thredsholdboxSize; i ++ ) {
                    for(int j = l - thredsholdboxSize; j < img6.cols; j++ ) {
                        if ( img6.at<uchar>( i , j ) > thredshold ) {
                            img6.at<uchar>( i , j ) = -1;
                        }
                        else {
                            img6.at<uchar>( i , j ) = C;
                        }
                    }
                }
            }
            if( k - thredsholdboxSize >= 0 && l - thredsholdboxSize >= 0 && k + thredsholdboxSize > img6.rows && l + thredsholdboxSize > img6.cols){
                int kk =  img6.rows - thredsholdboxSize;
                int ll = img6.cols - thredsholdboxSize;
                // Første firekant
                x1 = image4.otsuThredsholdValue(&img6, kk - thredsholdboxSize, ll - thredsholdboxSize, thredsholdboxSize);
                // Anden firekant
                x2 = image4.otsuThredsholdValue(&img6, kk - thredsholdboxSize, ll, thredsholdboxSize);
                // Tredje firekant
                x3 = image4.otsuThredsholdValue(&img6, kk, ll - thredsholdboxSize, thredsholdboxSize);
                // Fjerde firekant
                x4 = image4.otsuThredsholdValue(&img6, kk, ll, thredsholdboxSize);
                
                thredshold = cvRound( ((x1 + x2 + x3 + x4) / 4) - C );
                if(thredshold < 0) {
                    thredshold = C;
                }
                for(int i = k - thredsholdboxSize; i < img6.rows; i ++ ) {
                    for(int j = l - thredsholdboxSize; j < img6.cols; j++ ) {
                        if ( img6.at<uchar>( i , j ) > thredshold ) {
                            img6.at<uchar>( i , j ) = -1;
                        }
                        else {
                            img6.at<uchar>( i , j ) = 0;
                        }
                    }
                }
            }
            
            if( k - thredsholdboxSize >= 0 && l - thredsholdboxSize >= 0 && k + thredsholdboxSize > img6.rows && l + thredsholdboxSize < img6.cols){
                int kk =  img6.rows - thredsholdboxSize;
                // Første firekant
                x1 = image4.otsuThredsholdValue(&img6, kk - thredsholdboxSize, l - thredsholdboxSize, thredsholdboxSize);
                // Anden firekant
                x2 = image4.otsuThredsholdValue(&img6, kk - thredsholdboxSize, l, thredsholdboxSize);
                // Tredje firekant
                x3 = image4.otsuThredsholdValue(&img6, kk, l - thredsholdboxSize, thredsholdboxSize);
                // Fjerde firekant
                x4 = image4.otsuThredsholdValue(&img6, kk, l, thredsholdboxSize);
                
                thredshold = cvRound( ((x1 + x2 + x3 + x4) / 4) - C );
                if(thredshold < 0) {
                    thredshold = C;
                }
                for(int i = k - thredsholdboxSize; i < img6.rows; i ++ ) {
                    for(int j = l - thredsholdboxSize; j < l + thredsholdboxSize; j++ ) {
                        if ( img6.at<uchar>( i , j ) > thredshold ) {
                            img6.at<uchar>( i , j ) = -1;
                        }
                        else {
                            img6.at<uchar>( i , j ) = 0;
                        }
                    }
                }
            }
        l += increment;
        }
    k += increment;
    }
    
    image4.showImage(&img6, "adapted");

}
