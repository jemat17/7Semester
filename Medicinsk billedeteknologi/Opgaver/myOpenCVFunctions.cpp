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

void myOpencvFucntions::binarthredsholdedImage(cv::Mat *image) {
    /*
    Ændre forholdet i < 120 = -1 hvis hvid baggrund --> Dette inverter billedet. 
    */
    
    for( int i = 0; i < image->rows; i++ ) {
        for( int j = 0; j < image->cols; j++) {
            if( image->at<uchar>( i , j ) < 120 ) { //Aner ikke om 120 er en god værdi
                image->at<uchar>( i , j ) = -1;
            }else { 
                image->at<uchar>( i , j ) = 0;
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

Tjek venstre og op --> brug c++ funcitionen min( X, Y)

uchar til 32 bit, overflow med label (4007)
*/

void myOpencvFucntions::connectedComponentsAnalysisFour(cv::Mat *thresholdImage){
    thresholdImage->convertTo(*thresholdImage, CV_32FC1);
    // Thredshold billedet.
    for( int i = 0; i < thresholdImage->rows; i++ ) {
        for( int j = 0; j < thresholdImage->cols; j++) {
            if( thresholdImage->at<float>( i , j ) < 120 ) { //Aner ikke om 120 er en god værdi
                thresholdImage->at<float>( i , j ) = -1;
            }else { 
                thresholdImage->at<float>( i , j ) = 0;
            }
        }
    }
    
     erodeDilate(thresholdImage);

    int label = 0;
    for( int i = 1; i < thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < thresholdImage->cols -1; j++ ) {
           
            // Check that the value at (i , j) is -1
            if( thresholdImage->at<float>( i , j ) == -1 ) {
                // Check that the pixels above and to the left is not assigned a label.
                if(((thresholdImage->at<float>(i-1, j)) == 0) && ((thresholdImage->at<float>(i,j-1)) == 0)) {
                        thresholdImage->at<float>( i , j ) = label++; // create new label.
                    }
                else{
                        // First check, one bigger than zero and the other is 0
                        if((thresholdImage->at<float>( i-1 , j ) != 0) && (thresholdImage->at<float>( i , j-1 ) == 0)) {
                             thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i-1 , j );
                        }
                        if((thresholdImage->at<float>( i-1 , j ) == 0) && (thresholdImage->at<float>( i , j-1 ) != 0)){
                             thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i , j-1 );
                        }
                        // Check what label is smallst if both is above 0 and they not are equal to each other
                         if(!(thresholdImage->at<float>( i , j-1 ) == (thresholdImage->at<float>( i-1 , j )))){
                            thresholdImage->at<float>( i , j ) = std::min(thresholdImage->at<float>( i-1 , j ) , thresholdImage->at<float>( i , j-1 ));  
                        } 
                        // Assign label if they are equal to each other.
                        if((thresholdImage->at<float>( i , j-1 )) == (thresholdImage->at<float>( i-1 , j ))){
                            thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i-1 , j );    
                        }
                    } 
                }
            }
        }
    
    std::cout << *thresholdImage;
    std::cout << label;
    cv::namedWindow("img at first label", cv::WINDOW_AUTOSIZE);
    cv::imshow("img at first label", *thresholdImage);
    cv::waitKey(0);
    /*
    * Check with vector pair if the correct label is assigned. 
    * Using a cross to check too be sure.
    */
    std::vector< std::pair < int , int > >  conflicts;
    for( int i = 1; i < thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < thresholdImage->cols -1; j++ ) {
            if( thresholdImage->at<float>( i , j ) > 0 ) {
                int arr[4] = {0};
                arr[0] = thresholdImage->at<float>( i-1 , j );
                arr[1] = thresholdImage->at<float>( i , j-1 );
                arr[2] = thresholdImage->at<float>( i-1 , j );
                arr[3] = thresholdImage->at<float>( i , j-1 );

                int min = thresholdImage->at<float>( i , j );
                for( int k = 0; k < 4; k++) {
                    if(arr[k] < min) {
                        if(arr[k] > 0) {
                            min = arr[k];    
                        }
                    }
                }
                conflicts.push_back(std::make_pair(thresholdImage->at<float>( i , j ), min));
            }
        }
    }
    
    /* Ret alle pixels med conflicts vectoren.  */

    for( int i = thresholdImage->rows -1; i >= 0; i-- ) {
        for( int j = thresholdImage->cols -1; j >= 0 ; j-- ) { 
            for(int h = (int)conflicts.size() -1; h >= 0 ; h--) {  // Hvordan løses den her?
                if(thresholdImage->at<float>( i , j ) == conflicts[h].first)
                    thresholdImage->at<float>( i , j ) = conflicts[h].second;
            }
        }
    }
    cv::namedWindow("img after label is done", cv::WINDOW_AUTOSIZE);
    cv::imshow("img after label is done", *thresholdImage);
    cv::waitKey(0);

    // Farvelæg billedet med grå toner
    int arr[conflicts.size()+1] = {0};
    for(int g = 0; g < 5; g++){
    for( int i = 0; i < thresholdImage->rows; i++ ) {
        for( int j = 0; j < thresholdImage->cols; j++ ) {
            for( int k = 0; k < (int)conflicts.size(); k++){  // Hvordan løses denne warning?
                if( thresholdImage->at<float>( i , j ) == conflicts[k].second ) {
                    thresholdImage->at<float>( i , j ) = 255 - k;
                    arr[k]++;
                }
                }
            }  
        }
    }
    std::cout << "Rows: "<< thresholdImage->rows << " Cols: " <<  thresholdImage->cols << " sum: " << thresholdImage->rows*thresholdImage->cols << std::endl;
    std::cout << "label: " << label << std::endl; 
    for(int i = 1; i <= label; i++){
        if(arr[i] > 0) {
            std::cout << "label: " << i << " " << arr[i] << std::endl;
        }
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
void myOpencvFucntions::erodeDilate(cv::Mat *thresholdImage) {
    cv::Mat modified;
    cv::Mat kernal = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));

    cv::erode(*thresholdImage, modified, kernal );
    cv::dilate(modified, *thresholdImage, kernal);

}

void myOpencvFucntions::RCC(cv::Mat *thresholdImage, int i, int j, int label) {
    if(!(i-1 < 1) || !(j < 1) || !(i-1 > thresholdImage->cols -1) || !(j > thresholdImage->cols -1)){
        if(thresholdImage->at<uchar>( i-1 , j ) == 255 ){
            thresholdImage->at<uchar>( i-1 , j ) = label;
            RCC(thresholdImage, i-1, j, label);
        }
    }
    if(!(i < 1) || !(j-1 < 1) || !(i > thresholdImage->cols -1) || !(j-1 > thresholdImage->cols -1)) {
        if(thresholdImage->at<uchar>( i , j-1 ) == 255 ){
            thresholdImage->at<uchar>( i , j-1 ) = label;
            RCC(thresholdImage, i, j-1, label);
        }
    }
    if(!(i+1 < 1) || !(j < 1) || !(i+1 > thresholdImage->cols -1) || !(j > thresholdImage->cols -1)){
        if(thresholdImage->at<uchar>( i+1 , j ) == 255 ){
            thresholdImage->at<uchar>( i+1 , j ) = label;
            RCC(thresholdImage, i+1, j, label);
        }
    }
    if(!(i < 1) || !(j+1 < 1) || !(i > thresholdImage->cols -1) || !(j+1 > thresholdImage->cols -1)){
        if(thresholdImage->at<uchar>( i , j+1 ) == 255 ){
            thresholdImage->at<uchar>( i , j+1 ) = label;
            RCC(thresholdImage, i, j+1, label);
        }
    }
}


void myOpencvFucntions::connectedComponentsAnalysisRecursion(cv::Mat *thresholdImage) {
    erodeDilate(thresholdImage);

    int label = 0;
    for(int i = 1; i < thresholdImage->rows-1; i++) {
        for(int j = 1; j < thresholdImage->cols-1; j++) {
            if( thresholdImage->at<uchar>( i , j ) == 255 ){
                label++;
                RCC(thresholdImage, i, j, label);
            }
        }
    }
    int arr[label+1] = {0};
    for(int i = 1; i < thresholdImage->rows -1; i++) {
        for(int j = 1; j < thresholdImage->cols -1; j++) {
            for(int k = 1; k <= label; k++) {
                if(thresholdImage->at<uchar>( i , j ) == k ) {
                    thresholdImage->at<uchar>( i , j ) = (255 * k) / label;
                    arr[k]++;
                }
            }
        }
    }
    //std::cout << *thresholdImage << std::endl;
    std::cout << "Rows: "<< thresholdImage->rows << " Cols: " <<  thresholdImage->cols << " sum: " << thresholdImage->rows*thresholdImage->cols << std::endl;
    std::cout << "label: " << label << std::endl; 
    for(int i = 1; i <= label; i++){
        if(arr[i] > 0 ){
            std::cout << "label: " << i << " " << arr[i] << std::endl;
        }
    }

}