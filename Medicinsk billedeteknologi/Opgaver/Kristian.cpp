#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
//int r, c, argc, ny_px; INGEN GLOBALE VARIABLER!
void filter(Mat image, Mat new_image);
int main(int argc, char** argv){
    Mat image1;
    
    String imageName("Happy_fish2.jpg"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    image1 = imread(samples::findFile(imageName), IMREAD_GRAYSCALE); // Read the file
    if (image1.empty())                      // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    Mat new_image2 = Mat::zeros(image1.rows, image1.cols, CV_8UC1); // Den her må først deklares efter image 1 er loaded ellers har den ingen dimentioner
    // og du får derfor en segmentation error.
    // Jeg har også ændret fra CV_64FC1 til CV_8UC1, ellers får vi et helt sort billede når vi bruger uchar i image.at<> (Jeg tror det er fordi det er forskellige størrelse bit).
   
    filter(image1, new_image2);

    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", image1);

    namedWindow("New_image", WINDOW_AUTOSIZE);
    imshow("New_image", new_image2);
    waitKey();
}
void filter(Mat image, Mat new_image){
    for (int r = 1; r < image.rows-1; r++) { //Der skal være plads til filteret så til rows -1 så længe du ikke har padding på.
        for (int c = 1; c < image.cols-1; c++) { // Samme som oven over
            float sum = 0; // For ikke bare at have en sum der stikker af skal den nulstilles hver gang filteret skifter midter pixel.
            for (int m = r-1; m < r+2; m++) { //Ændret til r-1 og r+2 så den følger med rundt i billedet
                for (int l = c-1; l < c+2; l++) { // Samme som oven over.
                    sum += image.at<uchar>(m, l);
                    /*ny_px = round(sum / 9); 
                    Du gemmer alligevel summen i sum.
                    istedet har jeg ændret det så du sætter sum/9 ind i new_image.at men det gør ingen forskel ud over at være en operation mindre i dit for loop *9*799*799 */
                }
            }
            new_image.at<uchar>(r,c) = round(sum/9);
        } 
    }
}

/* 
Jeg har skrevet et par kommentare til din kode der hvor jeg har lavet nogle ændringer.
Spørg hvis der er noget der ikke giver mening. 
Sig til hvis du gerne vil ændre funktionen til call by refference. Jeg vil gerne vise og forklare dig hvordan :)
*/