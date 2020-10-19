// Copyright Non!
// Author: Jeppe Dreyer Matzen
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
void myOpencvFucntions::histogramChanger(cv::Mat *image) {
    int histogram[256] = {0};

    for(int i= 0; i < (int)((sizeof(histogram))/(sizeof(histogram[0]))); i++){
        histogram[i] = 0;
    }
    for(int i = 0; i < image->rows; i++) {
       for( int j = 0; j < image->cols; j++) {
            histogram[image->at<uchar>( i , j )]++;
        }
    }

    for(int i= 1; i < (int)((sizeof(histogram))/(sizeof(histogram[0]))); i++){
        if(histogram[i] > 30000 || (histogram[i] > histogram[i - 1] *1.3 && histogram[i] > histogram[i + 1] *1.3 ) ) {
            for(int j = 0; j < image->rows; j++) {
                for(int k = 0; k < image->cols; k++) {
                    if(image->at<uchar>( j , k ) == i) {
                        image->at<uchar>( j , k ) = 0;//(histogram[i - 1] + histogram[i + 1]) / 2 ;
                    }
                 }
            }
        }               
     } 
}

void myOpencvFucntions::calHistogram(cv::Mat *image, std::string name) {
    int histogramBinCount[256] = {0};

    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        histogramBinCount[i] = 0;
        }

    for(int i = 0; i < image->rows; i++) {
        for( int j = 0; j < image->cols; j++) {
            histogramBinCount[image->at<uchar>( i , j )]++;
        }
    }

    cv::Mat bins = cv::Mat::zeros(windowSize,windowSize, CV_8UC1 ); 

     /*Find max pixel value*/
    float numPixel = image->rows * image->cols;
    float rangeOfPixels;
    int maxOfPixels = histogramBinCount[0   ];
    rangeOfPixels = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));

    for(int i = 0; i < rangeOfPixels; i++) {
        if(histogramBinCount[i] > maxOfPixels) {
            maxOfPixels = histogramBinCount[i];
        }
    }

    // Normalise
    for(int i = 0; i < rangeOfPixels; i++)
    {
       float normalizedHeightOfBin = (histogramBinCount[i]/numPixel) * windowSize; // scale til windowsize 
       cv::line
            (
           bins, 
           cv::Point(i* (windowSize / rangeOfPixels) , windowSize), 
           cv::Point(i* (windowSize / rangeOfPixels) , windowSize - normalizedHeightOfBin*50), // Find en bedre måde at scalere på, der ikke giver overflow! 
           cv::Scalar::all(255) //hvid farve
           );
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

    cv::Mat modified;
    cv::Mat kernal = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));

    cv::erode(*thresholdImage, modified, kernal );
    cv::dilate(modified, *thresholdImage, kernal);

}




void myOpencvFucntions::RCC(cv::Mat *thresholdImage, int i, int j, int label) {

    if(!(i-1 < 1) || !(j < 1) || !(i-1 > thresholdImage->cols -1) || !(j > thresholdImage->cols -1)){
        if((int)thresholdImage->at<uchar>( i-1 , j ) == 255 ){
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
    float histogramBinCount[256] = {0};
    int sizeOfImage = image->rows * image->cols;
    
    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        histogramBinCount[i] = 0;
        }

    for(int i = 0; i < image->rows; i++) {
        for( int j = 0; j < image->cols; j++) {
            histogramBinCount[image->at<uchar>( i , j )]++;
        }
    }
    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
            histogramBinCount[i] =  histogramBinCount[i] / sizeOfImage ;
        }
    
    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        if( histogramBinCount[i] >  0.001 &&  i > max) { // En pixel skal udgøre mere end 1 procent af billedet for at blive talt med
            max = i;
        }
        if( histogramBinCount[i] >  0.001 &&  i < min) {
            min = i;
        }
    } 

    for(int i = 0; i < image->rows; i++) {
        for(int j = 0; j < image->cols; j++) {
            image->at<uchar>( i , j ) = round( ((int)(image->at<uchar>( i , j ) - min) * 255) / ( max - min )); 
        }
    }
}


void myOpencvFucntions::otsuThredshold(cv::Mat *image){
    long double histogramBinCount[256] = {0};

    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        histogramBinCount[i] = 0;
        }

    for(int i = 0; i < image->rows; i++) {
        for( int j = 0; j < image->cols; j++) {
            histogramBinCount[image->at<uchar>( i , j )]++;
        }
    }

    cv::Mat bins = cv::Mat::zeros(windowSize,windowSize, CV_8UC1 ); 

     /*Find max pixel value and normalize*/
    long double numPixel = image->rows * image->cols, Totalmean = 0;
    float rangeOfPixels = (sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]));

    for(int i = 0; i < rangeOfPixels; i++) {
        histogramBinCount[i] /= numPixel;
        Totalmean += (i+1) * histogramBinCount[i]; //Total mean
    }
    // Otsu part:
    // husk 1-256 så 0 ikke bliver ganget med 0
    long double weight = 0, max = 0, classVar = 0, mean = 0;
    int thredsval = 0;

    for(int i= 0; i < (int)((sizeof(histogramBinCount))/(sizeof(histogramBinCount[0]))); i++){
        
        weight += histogramBinCount[i];
        mean += (i+1) * histogramBinCount[i];

        classVar = pow((( Totalmean * weight ) - mean ) , 2 ) / ( weight * ( 1 - weight ));

        if(max < classVar){
            max = classVar;
            thredsval = i;
        }
    } 
    for(int i = 0; i < image->rows; i++) {
        for( int j = 0; j < image->cols; j++) {
            if ( image->at<uchar>( i , j ) > thredsval ) {
                image->at<uchar>( i , j ) = -1;
            }
            else {
                image->at<uchar>( i , j ) = 0;
            }
        }
    }
}