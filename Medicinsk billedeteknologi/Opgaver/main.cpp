#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <math.h>
#include "myOpenCVFunctions.h"

int main()
{
     
     
    // /* 
    // Opgave 2: Calculate and plot the histogram of the Your_xray.png.

    // This will display calculate the histogram, normalize it and then scale it accoringly to the window size and largest count.  

    // */

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

    std::string name2 = "Stretched Histogram";
    image.stretchHistogram(&img1);
    image.calHistogram(&img1, name2);
    
    /*
    Opgave 4: Implement and apply image invert. 
    */
    
    image.invaterGrayImage(&img2);

    image.showImage(&img2, "Inverted image");

    /*
    Opgave 5: For the Xray image (Your_xray.png), apply a 3x3 filtering method and describe the effect.
    */
    
    float padding = 3;
    cv::Mat kernel = cv::Mat::ones( padding, padding, CV_8UC1 );
    cv::Mat paddedImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1), image.getCols(&img1) + (padding-1), CV_8UC1 );
    cv::Mat filteredImage = cv::Mat::zeros(image.getRows(&img1) + (padding-1),  image.getCols(&img1) + (padding-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding, &paddedImage);
    image.filter(&paddedImage, &padding, &filteredImage, &kernel); 
    
    image.showImage(&filteredImage, "Image with 3X3 filter");

    /*
    Opgave 6: Extend the filtering method to include filters of size 5x5. 
        - What happens to the resulting image size when the filter size increases (3x3 vs. 5x5)?
        - Implement a way to avoid this effect.
        - Compare your implementation to what happens if you use the GausianBlur OpenCV function (see online documentation).
    */
    
    float padding2 = 5;
    cv::Mat kernel2 = cv::Mat::ones( padding2, padding2, CV_8UC1 );
    cv::Mat paddedImage2 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1), image.getCols(&img1) + (padding2-1), CV_8UC1 );
    cv::Mat filteredImage2 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1),  image.getCols(&img1) + (padding2-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding2, &paddedImage2);
    image.filter(&paddedImage2, &padding2, &filteredImage2, &kernel2); 
    
    image.showImage(&filteredImage2, "Image with 5X5 filter");

    // I have the option to use GausianBlur as well.
    int kernelData[] = {1, 4, 7, 4, 1, 
                        4, 16, 26, 16, 4, 
                        7, 26, 41, 26, 7, 
                        4, 16, 26, 16, 4, 
                        1, 4, 7, 4, 1};
    cv::Mat kernelCostum( padding2, padding2, CV_8UC1, kernelData);
    cv::Mat paddedImage3 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1), image.getCols(&img1) + (padding2-1), CV_8UC1 );
    cv::Mat filteredImage3 = cv::Mat::zeros(image.getRows(&img1) + (padding2-1),  image.getCols(&img1) + (padding2-1), CV_8UC1 );

    image.zeroPadding(&img1, &padding2, &paddedImage3);
    image.filter(&paddedImage3, &padding2, &filteredImage3, &kernelCostum); 
    
    image.showImage(&filteredImage3, "Image with 5X5 Gausian filter");

    // Build in OpenCV GaussianBlur function
    cv::Mat blur;
    GaussianBlur(img1, blur, cv::Size(5,5),0);
    image.showImage(&filteredImage3, "Image with OpenCV 5X5 Gausian filter");

    

    /*
    Opgave 7: A clearer delineation of the 4 heart chambers and 2 valves visible in the image (Heart.png) is desired. 
    Explain and implement a way to achieve this as best as possible using a combination of the given tools. 
    */
    cv::Mat heart;
    std::string namefile2 = "heart.png";
    myOpencvFucntions imageHeart(&heart, &type, namefile2);

    float heartPadding = 3;
    cv::Mat heartPaddedImage = cv::Mat::zeros(imageHeart.getRows(&heart) + (heartPadding-1), imageHeart.getCols(&heart) + (heartPadding-1), CV_8UC1 );
    cv::Mat heartFilteredImage = cv::Mat::zeros(imageHeart.getRows(&heart) + (heartPadding-1),  imageHeart.getCols(&heart) + (heartPadding-1), CV_8UC1 );
    cv::Mat heartkernel = cv::Mat::ones( heartPadding, heartPadding, CV_8UC1 );

    imageHeart.showImage(&heart, "Heart Image unedit");
    
    //imageHeart.stretchHistogram(&heart); 
    
    //imageHeart.calHistogram(&heart, "Histogram Heart");
    /*
    imageHeart.erodeDilate(&heart);

    imageHeart.zeroPadding(&heart, &heartPadding, &heartPaddedImage);
    //imageHeart.filter(&heart, &heartPadding, &heartFilteredImage, &heartkernel);
    GaussianBlur(heart, heartFilteredImage, cv::Size(5,5),0);
    imageHeart.showImage(&heartFilteredImage, "Heart Image 1");

    imageHeart.invaterGrayImage(&heartFilteredImage);
    imageHeart.calHistogram(&heartFilteredImage, "Histogram Heart 2");
    imageHeart.showImage(&heartFilteredImage, "Heart Image 2");
    imageHeart.erodeDilate(&heartFilteredImage);

    imageHeart.binarthredsholdedImage(&heartFilteredImage, 135);  //165 forsvinder højre bund. 100 for lavt (130-135 bedste bud)
    
    cv::Mat kernal = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));

    */
    imageHeart.showImage(&heartFilteredImage, "Heart Image 3");

    /* 
    Opgave 8: Explain what the function: void inverseDFT(const std::string&  filename)  found in the fft.cpp file does. 
    */
    cv::destroyAllWindows();
    return 0;

}