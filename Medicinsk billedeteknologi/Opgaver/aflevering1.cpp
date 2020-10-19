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
    // Opgave 2: Calculate and plot the histogram of the Your_xray.png.

    //This will display calculate the histogram, normalize it and then scale it accoringly to the window size and largest count.  

      int type = 0; // 0 (grayscale), 1 (color), -1 (unchanged)
    cv::Mat img1, img2;
    std::string name1 = "Histogram";
    std::string namefile1 = "Your_xray.png";
    myOpencvFucntions image(&img1, &type, namefile1);
    image.calHistogram(&img1, name1);
    img1.copyTo(img2);
   
    /* 
    Opgave 3: Implement and apply histogram stretch for the image. 
    */
   // This will stretch the pixels, calculate the histogram and print it 

    std::string name2 = "Stretched Histogram";
    image.stretchHistogram(&img1);
    image.calHistogram(&img1, name2);
    
    /*
    Opgave 4: Implement and apply image invert. 
    */

    // This will invert and show the image
    image.invaterGrayImage(&img2);
    image.showImage(&img2, "Inverted image");

    /*
    Opgave 5: For the Xray image (Your_xray.png), apply a 3x3 filtering method and describe the effect.
    */

    // This will run a 3X3 Averge filter on the image.
    // The effekt will be a blured image. The effekt will be more clear if I increase the kernel size. 
    float padding = 3;
    cv::Mat kernel = cv::Mat::ones( padding, padding, CV_8UC1 );
    cv::Mat paddedImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1), image.getCols(&img1) + (padding-1), CV_8UC1 ); // set up padding for image 
    cv::Mat filteredImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1),  image.getCols(&img1) + (padding-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding, &paddedImage); // Make padding for image
    image.filter(&paddedImage, &padding, &filteredImage, &kernel); 
    
    image.showImage(&filteredImage, "Image with 3X3 filter");

    /*
    Opgave 6: Extend the filtering method to include filters of size 5x5. 
        - What happens to the resulting image size when the filter size increases (3x3 vs. 5x5)?
        - Implement a way to avoid this effect.
        - Compare your implementation to what happens if you use the GausianBlur OpenCV function (see online documentation).
    */
    
    // This will run a 5X5 filter on the image
    float padding2 = 5; // Chose padding and kernel size.
    cv::Mat kernel2 = cv::Mat::ones( padding2, padding2, CV_8UC1 );
    cv::Mat paddedImage2 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1), image.getCols(&img1) + (padding2-1), CV_8UC1 ); // Set up padding for image
    cv::Mat filteredImage2 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1),  image.getCols(&img1) + (padding2-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding2, &paddedImage2); // Make padding for image
    image.filter(&paddedImage2, &padding2, &filteredImage2, &kernel2); 
    
    image.showImage(&filteredImage2, "Image with 5X5 filter");

    // I have the option to use GausianBlur as well, instead of using a kernel of ones I can chose the kernel date myself.
    int kernelData[] = {1, 4, 7, 4, 1, 
                        4, 16, 26, 16, 4, 
                        7, 26, 41, 26, 7, 
                        4, 16, 26, 16, 4, 
                        1, 4, 7, 4, 1};

    cv::Mat kernelCostum( padding2, padding2, CV_8UC1, kernelData);
    cv::Mat paddedImage3 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1), image.getCols(&img1) + (padding2-1), CV_8UC1 ); // Set up padding for image
    cv::Mat filteredImage3 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1),  image.getCols(&img1) + (padding2-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding2, &paddedImage3); // Make padding for image
    image.filter(&paddedImage3, &padding2, &filteredImage3, &kernelCostum);  // Gausian filter

    image.showImage(&filteredImage3, "Image with 5X5 Gausian filter");

    // Build in OpenCV GaussianBlur function
    cv::Mat blur;
    GaussianBlur(img1, blur, cv::Size(5,5),0);
    image.showImage(&filteredImage3, "Image with OpenCV 5X5 Gausian filter");

    

    /*
    Opgave 7: A clearer delineation of the 4 heart chambers and 2 valves visible in the image (Heart.png) is desired. 
    Explain and implement a way to achieve this as best as possible using a combination of the given tools. 
    */

    // Import image 
    cv::Mat heart;
    std::string namefile2 = "heart.png";
    myOpencvFucntions imageHeart(&heart, &type, namefile2);
    
    imageHeart.showImage(&heart, "Heart Image unedit");

    // 5X5 Gausian filter to remove noise 
    float heartPadding = 5; // Make padding and kernal size.
    int kernelData2[] = {1, 4, 7, 4, 1, 
                        4, 16, 26, 16, 4, 
                        7, 26, 41, 26, 7, 
                        4, 16, 26, 16, 4, 
                        1, 4, 7, 4, 1};
    cv::Mat kernelCostum2( heartPadding, heartPadding, CV_8UC1, kernelData2);
    cv::Mat heartFilteredImage = cv::Mat::zeros(imageHeart.getRows(&heart) + (heartPadding-1),  imageHeart.getCols(&heart) + (heartPadding-1), CV_8UC1 );
    cv::Mat heartkernel = cv::Mat::ones( heartPadding, heartPadding, CV_8UC1 );
    image.filter(&heart, &heartPadding, &heartFilteredImage, &kernelCostum2); 


    
    // Calculate the histogram to see the pixel distribution of the image (Stretch not a good idea)
    imageHeart.calHistogram(&heartFilteredImage, "Histogram Heart");
    
    // See the image. 
    imageHeart.showImage(&heartFilteredImage, "After filter");

    // Invert the image 
    imageHeart.invaterGrayImage(&heartFilteredImage);
    imageHeart.showImage(&heartFilteredImage, "Heart after invert");
    
    

    
    // Thredshold the picture with different values for specified areaes in the immage.

    // make sure we can see the the top left wall
    for( int i = 0; i < 1450; i++ ) {
        for( int j = 0; j < 2000; j++) {
            if( heartFilteredImage.at<uchar>( i , j ) < 176 ) { //Aner ikke om 120 er en god værdi
                heartFilteredImage.at<uchar>( i , j ) = -1;
            }else { 
                heartFilteredImage.at<uchar>( i , j ) = 0;
            }
        }
    }
    // Thredshold the rest with two for loop statements
    for( int i = 1450; i < heartFilteredImage.rows; i++ ) {
        for( int j = 0; j < 2000; j++) {
            if( heartFilteredImage.at<uchar>( i , j ) < 135 ) { //Aner ikke om 120 er en god værdi
                heartFilteredImage.at<uchar>( i , j ) = -1;
            }else { 
                heartFilteredImage.at<uchar>( i , j ) = 0;
            }
        }
    }
    for( int i = 0; i < heartFilteredImage.rows; i++ ) {
        for( int j = 2000; j < heartFilteredImage.cols; j++) {
            if( heartFilteredImage.at<uchar>( i , j ) < 135 ) { //Aner ikke om 120 er en god værdi
                heartFilteredImage.at<uchar>( i , j ) = -1;
            }else { 
                heartFilteredImage.at<uchar>( i , j ) = 0;
            }
        }
    }
    imageHeart.erodeDilate(&heartFilteredImage);
    // Show the final image
    imageHeart.showImage(&heartFilteredImage, "Final image of heart");
    /* 
    Opgave 8: Explain what the function: void inverseDFT(const std::string&  filename)  found in the fft.cpp file does. 
    */
    cv::destroyAllWindows();
    return 0;


}
