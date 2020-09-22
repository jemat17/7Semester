#include "myOpenCVFunctions.h"

myOpencvFucntions::myOpencvFucntions(cv::Mat *img, int *type)
    {
        std::string nameOfFile;
        std::cout << "What is the name of your image?" << std::endl;
        std::cin >> nameOfFile;
        nameOfFile += ".jpg";
        *img = cv::imread(nameOfFile, *type);
        system("clear");
    }



void myOpencvFucntions::calHistogram(cv::Mat *image) {
    
    for (int i = 0; i<image->rows; i++) {
        for (int j = 0; j<image->cols; j++) {
            histogramBinCount[image->at<uchar>(i,j)]++; // Vælg < > efter type af billede, grayscale: 8 bit (ex uint8_t) 
        /* 
            Farve: <Vec3d> så den ved der er tre kanaler
            Her til går den kun den første pixel (blå) RGB er omvendt i openCV så den hedder BGR
            image.at<uint8_t>(i,j)[0] // tilgår blå
            image.at<uint8_t>(i,j)[1] // tilgår grøn
            image.at<uint8_t>(i,j)[2] // tilgår rød
        */
        }
    }
    // Normalise
    float maxP = image->rows * image->cols;
    rangeOfPixels = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));
    float sum = 0;
    for(int i = 0; i < rangeOfPixels; i++) {
       float normalizedHeightOfBin = histogramBinCount[i]/maxP; //hvorfor normalisere vi med MAX?
       //std::cout << i << ":    " << normalizedHeightOfBin << std::endl; // show Histogram values
       sum += normalizedHeightOfBin;
       cv::line (
           bins, 
           cv::Point(i*(windowSize/rangeOfPixels), windowSize), cv::Point(i*(windowSize/rangeOfPixels), windowSize-normalizedHeightOfBin), // gange 100 for procent
           cv::Scalar::all(255) );//hvid farve
    }
    cv::imshow("name", bins);
}



int myOpencvFucntions::getCols(cv::Mat *image) {
    return image->cols;
}



int myOpencvFucntions::getRows(cv::Mat *image) {
    return image->rows;
}


/*
void myOpencvFucntions::filter(cv::Mat *imageIn, float *k, cv::Mat *imageOut, int weighted[3][3]){
    float indexCols = (sizeof weighted[0] / sizeof(int) - 1) / 2;
    float indexRows = (sizeof weighted / sizeof weighted[0] -1) / 2;
    for(int i = indexRows; i < imageIn->rows - indexRows; i++) {
        for(int j = indexCols; j < imageIn->cols - indexCols; j++) {
            int weightedCounter1 = 0;
            int weightedCounter2 = 0;
            float sum = 0;
            for(int b = i - indexRows; b <= i + indexRows; b++) {
                for(int h = j - indexCols; h <= j + indexCols; h++){
                    sum += imageIn->at<uchar>( b , h ) * weighted[weightedCounter1][weightedCounter2];
                    weightedCounter1++;
                    }  
                    weightedCounter2++;
                }
            imageOut->at<uchar>(i , j) =  round(sum / (*k * *k));
            }
           
        }
    }
*/
void myOpencvFucntions::zeroPadding(cv::Mat *image, float *k, cv::Mat *paddedImage){
    float index = (*k-1)/2;
    for(int i = 0; i < image->rows; i++) {
        for(int j = 0; j < image->cols; j++) {
            paddedImage->at<uchar>(i+index,j+index) = image->at<uchar>(i,j);
        }
    }

}


/*
Thredshold image:
*/

void myOpencvFucntions::thredsholdedImage(cv::Mat *image) {
    
    for( int i = 0; i < image->rows; i++ ) {
        for( int j = 0; j < image->cols; j++) {
            if( image->at<uchar>( i , j ) < 120 ) { //Aner ikke om 120 er en god værdi
                image->at<uchar>( i , j ) = 0;
            }else { 
                image->at<uchar>( i , j ) = -1;
            }
        }
    }
}


/* connectedComponentsAnalysisFour
1- Thredshold billedet så vi enten har sorte eller hvide pixels
2. Label scan med for loop hver gang vi møder nyt pixel vindue unden naboer nyt label
    If(igen nabo label++) 
    
    else if(nabo label update label list så vi ved at fx. 3 -> 2) 

3. label lighed ud fra label list
4. farv ift label
*/

void myOpencvFucntions::connectedComponentsAnalysisFour(cv::Mat *thresholdImage){
    int label = 0;
    for( int i = 1; i < thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < thresholdImage->rows -1; j++ ) {
            if( thresholdImage->at<uchar>( i , j ) == -1 ) {
                    if( !thresholdImage->at<uchar>( i-1, j ) > 0 && 
                        !thresholdImage->at<uchar>( i+1 , j ) > 0 && 
                        !thresholdImage->at<uchar>( i , j-1 ) > 0 &&
                        !thresholdImage->at<uchar>( i , j+1 ) > 0 ) {
                            thresholdImage->at<uchar>( i , j ) = label++; // fiks at lave nye labels
                        }
                    else {
                        int labelMin = 0;

                        if( thresholdImage->at<uchar>( i-1 , j ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i-1 , j );
                            }
                        else if( thresholdImage->at<uchar>( i+1 , j ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i+1 , j );
                            }       
                        else if( thresholdImage->at<uchar>( i , j-1 ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i , j-1 );
                            }
                        else if( thresholdImage->at<uchar>( i , j+1 ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i , j+1 );
                            }     

                        thresholdImage->at<uchar>( i , j ) = label; //label of lowest 
                        }
                        
                    }
                }

        }
        /*
        Her mangler jeg et tjek om det er den korrekte laveste label jeg sætter ind.
        Hvordan finder jeg sammenhæng mellem label.
        */
    for( int i = 1; i < thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < thresholdImage->rows -1; j++ ) {
            if( thresholdImage->at<uchar>( i , j ) > 0 ) {
                int labelMin = 0;

                        if( thresholdImage->at<uchar>( i-1 , j ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i-1 , j );
                            }
                        else if( thresholdImage->at<uchar>( i+1 , j ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i+1 , j );
                            }       
                        else if( thresholdImage->at<uchar>( i , j-1 ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i , j-1 );
                            }
                        else if( thresholdImage->at<uchar>( i , j+1 ) < labelMin) {
                            labelMin = thresholdImage->at<uchar>( i , j+1 );
                            }     

                        thresholdImage->at<uchar>( i , j ) = labelMin; //label of lowest 
            }
        }
    }
    FILE *fptr;
    fptr = fopen("output.txt", "w");
    for( int i = 0; i < thresholdImage->rows; i++ ) {
        for( int j = 0; j < thresholdImage->rows; j++ ) {
            fprintf(fptr, "%d", thresholdImage->at<uchar>( i , j ) );
            fprintf(fptr, "%s", " " );
            if( i == thresholdImage->rows -1) 
                fprintf(fptr, "%s\n", "" );
            for( int k = 1; k < label; k++){
                if( thresholdImage->at<uchar>( i , j ) == k ) {
                    thresholdImage->at<uchar>( i , j ) = 255-k*5;
                }
            }  
        }
    fclose(fptr);  
    }
}

/* connectedComponentsAnalysis recursion
1. Thredshold til og sæt 1 til minus 1 med for for 
2.  tjek billedet med for for -> for at finde de steder med minus -1
    if( i, j = -1)
        Rursion delen RCC( label, i, j, image)
            RCC skal tjekke om de omkring liggende er minus 1 hvis skal den kalde sig selv.
3. color++ 

*/
