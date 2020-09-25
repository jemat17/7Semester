void connectedcomponent_recusion (cv::Mat image, int threshold_VALUE, int erode_count, int dilate_count){
//thresholdding image
threshold(image, threshold_VALUE);
//erosion
cv::erode(image,image,cv::Mat(),cv::Point(-1,-1),erode_count,1,1);
//dialate
cv::dilate(image,image,cv::Mat(),cv::Point(-1,-1),dilate_count,1,1);
int farve = 1; // initialize blob color, and serves as blob count
for(int r=1; r<image.rows-1; r++) //row image
    {
        for(int c=1; c<image.cols-1; c++) //col image
            {
                    if(image.at<uchar>(r,c) == 255)
                    {
                        rcc(farve,r,c,image);
                        farve ++;
                    }
            }     
    }
}
//blob detection with row by row function
void connectedcomponent_rowbyrow(cv::Mat image, int threshold_VALUE, int erode_count, int dilate_count)
{
std::vector<std::pair<int, int>> conflicts;
int label = 1;
//thresholdding image
threshold(image, threshold_VALUE);
//erosion
cv::erode(image,image,cv::Mat(),cv::Point(-1,-1),erode_count,1,1);
//dialate
cv::dilate(image,image,cv::Mat(),cv::Point(-1,-1),dilate_count,1,1);
    for(int i=1; i<image.rows-1; i++){ //row image
        for(int j=1; j<image.cols-1; j++){
            if((int)image.at<uchar>(i,j) == 255){
                //look up surounding pixels
                int nabo_up = (int)image.at<uchar>(i-1,j);
                int nabo_left = (int)image.at<uchar>(i,j-1);
                //check conectivity left
                if(nabo_left !=0 && nabo_up == 0){
                    image.at<uchar>(i,j)=nabo_left;
                }
                //check conectivity up
                if(nabo_up !=0 && nabo_left == 0){
                    image.at<uchar>(i,j)=nabo_up;
                }
                if(nabo_up !=0 && nabo_left != 0 && nabo_left == nabo_up){
                    //set pixelvalue to nabo
                   image.at<uchar>(i,j)=nabo_left;
                }
                //check for conflict
                if(nabo_up !=0 && nabo_left != 0 && nabo_left != nabo_up){
                    int min = std::min(nabo_left,nabo_up);
                    int max = std::max(nabo_left,nabo_up);
                    //set pixelvalue to lowest in conflict
                   image.at<uchar>(i,j)=min;
                    //saving conflict
                    conflicts.push_back(std::make_pair(max, min));
                }
                //if no conflicts set to farve
                if(nabo_left == 0 && nabo_up == 0){
                    image.at<uchar>(i,j) = label;
                    label++;
                }
            }
        }     
    }
    //Solve conflicts
    for(int r=image.rows-1; r>=0; r--){ 
        for(int c=image.cols-1; c>=0; c--){           
            for(int i = conflicts.size()-1; i >= 0; i--){
                if((int)image.at<uchar>(r,c) == (int)conflicts[i].first){
                    image.at<uchar>(r,c) = conflicts[i].second;
                }
            }        
        }     
    }
}// end func