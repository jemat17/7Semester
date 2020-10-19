// Copyright Non!
// Author: Jeppe Dreyer Matzen
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
        /**
         * Constructor 
         * 
         *
         * @param values emty mat object, flag (0) for gray-scale, name of image
         * @return A image in the mat object
         */
        myOpencvFucntions(cv::Mat *img, int *type, std::string nameOfFile);
        /**
         * Shows image
         *
         * @param values image and string name
         * @return Displays image with window name from string
         */
        void showImage(cv::Mat *image, std::string name);        
        /**
         * Calculate the histogram of image
         * Scale from 0 to window size
         * 
         * @param values Takes image and string name
         * @return Override input with filtered image
         */
        void calHistogram(cv::Mat *image, std::string name);
        /**
         * Get cols
         * 
         *
         * @param values Takes image
         * @return num cols
         */
        int getCols(cv::Mat *image);
        /**
         * Get Rows
         * 
         *
         * @param values Takes image
         * @return num rows
         */
        int getRows(cv::Mat *image);
        /**
         * Filter function 
         * Runs a filter with size k and weight from kernal on image
         *
         * @param values image, size of filter, output image and kernal with weight values
         * @return Output image is a padded image
         */
        void filter(cv::Mat *imageIn, float *k, cv::Mat *imageOut, cv::Mat *kernal);
        /**
         * Padding function 
         * paddes image with 0
         *
         * @param values image, size of padding, and output image
         * @return Output image is a padded image
         */
        void zeroPadding(cv::Mat *image, float *k, cv::Mat *paddedImage);
        /**
         * Binary Thredshold function 
         * Turns a picture to 0 and 1 or 0 and -1 or 0 and 255
         *
         * @param values image and thredshold value
         * @return Overrides input with a binary image
         */
        void binarthredsholdedImage(cv::Mat *image, int tredsholdValue);
        /**
         * CCA four
         * Takes a binary picture by ref and overrides with the CCA.  
         *
         * @param values Image, Row, Col, label
         * @return Does not return an element, overrides input pixel with label.
         */
        void connectedComponentsAnalysisFour(cv::Mat *thresholdImage);
        /**
         * Recursive CCA
         * Takes a binary picture by ref and overrides with the CCA.  
         *
         * @param values Image, Row, Col, label
         * @return Does not return an element, overrides input pixel with label.
         */
        void connectedComponentsAnalysisRecursion(cv::Mat *thresholdImage);
        /**
         * Takes a  picture and runs a erode and a dilate function on it with a 3X3 kernel.
         *
         * @param values Mat image objekt
         * @return Does not return an element, overrides image with modified image.
        */
        void erodeDilate(cv::Mat *thresholdImage);

        /**
         * Recursive part of CCA function. 
         * The fist if statement makes sure we dont step outside of the picture
         * The second checks if a pixel in the cross  position is 255
         *
         * @param values Mat image objekt, Position i, j, label,  is cheched and if(TRUE) assinged to label
         * @return Does not return an element, overrides input pixel with label.
         */
        void RCC(cv::Mat *thresholdImage, int i, int j, int label);
        /**
         * Invert pixel values in an image.
         *
         * @param values Mat image objekt, Values are subtracted from 255.
         * @return Does not return an element, overrides input.
         */
        void invaterGrayImage(cv::Mat *image);
        /**
         * Stretch pixel values in an image.
         *
         * @param values Mat image objekt that are stretched from min to max of the image.
         * @return Does not return an element, overrides input.
         */
        void stretchHistogram(cv::Mat *image);
        void histogramChanger(cv::Mat *image);
        /**
         * Otsu thredshold 
         *  Finds the optimal thredshold for a image with a binorminal distribution.
         * 
         * @param values Mat image objekt.
         * @return Returns a thredsholded image
         */
        void otsuThredshold(cv::Mat *image);
    
    
    private:
    int windowSize = 700;
    
    

    
};


#endif
