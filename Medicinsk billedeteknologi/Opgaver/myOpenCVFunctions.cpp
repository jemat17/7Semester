#include "myOpenCVFunctions.h"

myOpencvFucntions::myOpencvFucntions(cv::Mat *img, int *type, std::string nameOfFile)
    {
        //std::cout << "What is the name of your image?" << std::endl;
        //std::cin >> nameOfFile;
        //nameOfFile += ".png";
        *img = cv::imread(nameOfFile, *type);
        
        system("clear");
    }

void myOpencvFucntions::showImage(cv::Mat *image, std::string name){
    cv::namedWindow(name, cv::WINDOW_NORMAL);
    cv::resizeWindow(name, 700, 700	);
    cv::imshow(name, *image); // Show window 
    cv::waitKey(0);
}

void myOpencvFucntions::calHistogram(cv::Mat *image, std::string name) {
    int histogramBinCount[256] = {0};
    float normalizedHeightOfBin[256];

    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        histogramBinCount[i] = 0;
        normalizedHeightOfBin[i] = 0;
        }
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
    int numberOfPixels = image->rows * image->cols, maxPixel = 0;
    
    int rangeOfPixels = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));
    
    for(int i = 0; i < rangeOfPixels; i++) {
        // Normalise 
        normalizedHeightOfBin[i] = (double)(histogramBinCount[i]/ numberOfPixels); 
        // Find max for scale in histogram
        if(normalizedHeightOfBin[i] > maxPixel) {
            maxPixel = normalizedHeightOfBin[i];
        }
    }

    cv::Mat bins = cv::Mat::zeros(windowSize, windowSize, CV_8UC1 );
    for(int i = 0; i < rangeOfPixels; i++) { 
        // Scale for hight of histogram 
       float normalizedHeightOfBinScaled = (normalizedHeightOfBin[i] * windowSize) / maxPixel;       
       cv::line (
           bins, 
           cv::Point(i*(windowSize/rangeOfPixels), windowSize), cv::Point(i*(windowSize/rangeOfPixels), windowSize-normalizedHeightOfBinScaled),
           cv::Scalar::all(255) );//hvid farve
    }
    showImage(&bins, name);
}

int myOpencvFucntions::getCols(cv::Mat *image) {
    return image->cols;
}



int myOpencvFucntions::getRows(cv::Mat *image) {
    return image->rows;
}



void myOpencvFucntions::filter(cv::Mat *imageIn, float *k, cv::Mat *imageOut, cv::Mat *kernal){
    float index = (*k-1)/2; // A number for indexing correct acording to padding size

    // Step through pixels and calculate the sum of a filter and devide by filter size (K*K)
    for(int i = index; i < imageIn->rows - index; i++) {
        for(int j = index; j < imageIn->cols - index; j++) {
            float sum = 0;
            float sumOfKernel = 0;
            int counter1 = 0, counter2 = 0;
            for(int b = i - index; b <= i + index; b++) {
                for(int h = j - index; h <= j + index; h++){
                    sum += imageIn->at<uchar>( b , h ) * kernal->at<uchar>(counter1 , counter2);
                    sumOfKernel += kernal->at<uchar>(counter1 , counter2);
                    counter2++;
                    }
                counter2 = 0;     
                counter1++; 
                }
            imageOut->at<uchar>(i , j) =  round(sum / sumOfKernel);
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

void myOpencvFucntions::binarthredsholdedImage(cv::Mat *image, int tredsholdValue) {
    /*
    Ændre forholdet i < 120 = -1 hvis hvid baggrund --> Dette inverter billedet. 
    */
    
    for( int i = 0; i < image->rows; i++ ) {
        for( int j = 0; j < image->cols; j++) {
            if( image->at<uchar>( i , j ) < tredsholdValue ) { //Aner ikke om 120 er en god værdi
                image->at<uchar>( i , j ) = -1;
            }else { 
                image->at<uchar>( i , j ) =0;
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
    for( int i = 1; i < thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < thresholdImage->cols -1; j++) {
            if( thresholdImage->at<float>( i , j ) < 200 ) { 
                thresholdImage->at<float>( i , j ) = -1;
            }else { 
                thresholdImage->at<float>( i , j ) = 0;
            }
        }
    }
    
     erodeDilate(thresholdImage);

    int label = 0;
    for( int i = 1; i < thresholdImage->rows-1; i++ ) {
        for( int j = 1; j < thresholdImage->cols-1; j++ ) {
           
            // Check that the value at (i , j) is -1
            if( (int)thresholdImage->at<float>( i , j ) == -1 ) {
                // Check that the pixels above and to the left is not assigned a label.
                if(((int)thresholdImage->at<float>(i-1, j) == 0) && ((int)thresholdImage->at<float>(i,j-1) == 0)) {
                        thresholdImage->at<float>( i , j ) = label++; // create new label.
                    }
                else{
                        // First check, one bigger than zero and the other is 0
                        if(((int)thresholdImage->at<float>( i-1 , j ) != 0) && (int)(thresholdImage->at<float>( i , j-1 ) == 0)) {
                             thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i-1 , j );
                        }
                        if(((int)thresholdImage->at<float>( i-1 , j ) == 0) && ((int)thresholdImage->at<float>( i , j-1 ) != 0)){
                             thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i , j-1 );
                        }
                        // Check what label is smallst if both is above 0 and they not are equal to each other
                         if(((int)thresholdImage->at<float>( i , j-1 ) != ((int)thresholdImage->at<float>( i-1 , j ))) && ((int)thresholdImage->at<float>( i , j-1 ) != 0 && ((int)thresholdImage->at<float>( i-1 , j ) != 0))){
                            thresholdImage->at<float>( i , j ) = std::min(thresholdImage->at<float>( i-1 , j ) , thresholdImage->at<float>( i , j-1 ));  
                        } 
                        // Assign label if they are equal to each other.
                        if(((int)thresholdImage->at<float>( i , j-1 )) == ((int)thresholdImage->at<float>( i-1 , j )) && (thresholdImage->at<float>( i , j-1 ) != 0)){
                            thresholdImage->at<float>( i , j ) = thresholdImage->at<float>( i-1 , j );    
                        }
                    }
                }
            }
        }
    /*
    * Check with vector pair if the correct label is assigned. 
    * Using a cross to check too be sure.
    */
    std::vector< std::pair < int , int > >  conflicts;
    for( int i = 1; i < (int)thresholdImage->rows -1; i++ ) {
        for( int j = 1; j < (int)thresholdImage->cols -1; j++ ) {
            if( (int)thresholdImage->at<float>( i , j ) > 0 ) {
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
                if((int)thresholdImage->at<float>( i , j ) != min) {
                    conflicts.push_back(std::make_pair(thresholdImage->at<float>( i , j ), min));
                }
            }
        }
    }
    
    /* Ret alle pixels med conflicts vectoren.  */
    for( int i = (int)thresholdImage->rows -1; i >= 0; i-- ) {
        for( int j = (int)thresholdImage->cols -1; j >= 0 ; j-- ) { 
            for(int h = (int)conflicts.size() -1; h >= 0 ; h--) {  
                if((int)thresholdImage->at<float>( i , j ) == conflicts[h].first)
                    thresholdImage->at<float>( i , j ) = conflicts[h].second;
            }
        }
    }

    // Farvelæg billedet med grå toner
    int arr[conflicts.size()+1] = {0};
    for( int i = 0; i < (int)thresholdImage->rows; i++ ) {
        for( int j = 0; j < (int)thresholdImage->cols; j++ ) {
            for( int k = 0; k < (int)conflicts.size(); k++){ 
                if( (int)thresholdImage->at<float>( i , j ) == conflicts[k].second ) {
                    thresholdImage->at<float>( i , j ) = 255-k;
                    arr[k]++;
                }
                }
            }  
        }

    // Print details about picture and number and size of labels. 
    std::cout << "Rows: "<< thresholdImage->rows << " Cols: " <<  thresholdImage->cols << " sum: " << thresholdImage->rows*thresholdImage->cols << std::endl;
    std::cout << "label: " << label << std::endl; 
    for(int i = 0; i <= label; i++){
        if(arr[i] > 0) {
            std::cout << "label: " << i << " " << arr[i] << std::endl;
        }
    }
    
}

void myOpencvFucntions::erodeDilate(cv::Mat *thresholdImage) {
    /*
    * Takes a binary picture and runs a erode and a dilate function on it with a 3X3 kernel.
    */
    cv::Mat modified;
    cv::Mat kernal = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));

    cv::erode(*thresholdImage, modified, kernal );
    cv::dilate(modified, *thresholdImage, kernal);

}


/* connectedComponentsAnalysis recursion
1. Thredshold til og sæt 1 til minus 1 med for for 
2.  tjek billedet med for for -> for at finde de steder med minus -1
    if( i, j = -1)
        Rursion delen RCC( label, i, j, image)
            RCC skal tjekke om de omkring liggende er minus 1 hvis skal den kalde sig selv.
3. color++ 

*/
void myOpencvFucntions::RCC(cv::Mat *thresholdImage, int i, int j, int label) {
    /*
    * Recursive part of CCA function. 
    * The fist if statement makes sure we dont step outside of the picture
    * The second checks if a pixel in the cross  position is 255
    */
    if(!(i-1 < 1) || !(j < 1) || !(i-1 > thresholdImage->cols -1) || !(j > thresholdImage->cols -1)){
        if(thresholdImage->at<uchar>( i-1 , j ) == 255 ){
            thresholdImage->at<uchar>(  i-1 , j ) = label;
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
    /*
    Recursive CCA
    Takes a binary picture by ref and overrides with the CCA.  
    */
    erodeDilate(thresholdImage);
    //Create label = 0 so first label will be one.
    // step through pixels, if pixel == 255 call recursion and increment label.
    int label = 0;
    for(int i = 1; i < thresholdImage->rows-1; i++) {
        for(int j = 1; j < thresholdImage->cols-1; j++) {
            if( thresholdImage->at<uchar>( i , j ) == 255 ){
                label++;
                RCC(thresholdImage, i, j, label);
            }
        }
    }
    // Change color of labels to make it easier to see. 
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
    // print details about picure and number and size of labels. 
    //std::cout << *thresholdImage << std::endl;
    std::cout << "Rows: "<< thresholdImage->rows << " Cols: " <<  thresholdImage->cols << " sum: " << thresholdImage->rows*thresholdImage->cols << std::endl;
    std::cout << "label: " << label << std::endl; 
    for(int i = 1; i <= label; i++){
        if(arr[i] > 0 ){
            std::cout << "label: " << i << " " << arr[i] << std::endl;
        }
    }

}

void myOpencvFucntions::invaterGrayImage(cv::Mat *image) { 
    for(int i = 0; i < image->rows; i ++) {
        for( int j = 0; j < image->cols; j++) {
            image->at<uchar>( i , j ) = 255 - (int)image->at<uchar>( i , j );
        }
    }
}

void myOpencvFucntions::stretchHistogram(cv::Mat *image){
    int max = 0, min = 255;
    
    for(int i = 0; i < image->rows; i++) {
        for(int j = 0; j < image->cols; j++) {
            if(image->at<uchar>( i , j ) > max ) {
                max = image->at<uchar>( i , j );
            }
            if( image->at<uchar>( i , j ) < min ) {
                min = image->at<uchar>( i , j );
            }
        }
    }

    for(int i = 0; i < image->rows; i++) {
        for(int j = 0; j < image->cols; j++) {
            image->at<uchar>( i , j ) = ( (int)(image->at<uchar>( i , j ) - min) * 255) / ( max - min ); 
        }
    }
}