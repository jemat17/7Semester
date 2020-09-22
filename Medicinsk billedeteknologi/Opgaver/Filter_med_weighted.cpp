#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void filter(Mat image, int filterfunc[3][3], Mat new_image);

int main(int argc, char** argv) {
    Mat image1;

    String imageName("sample.jpg"); // by default
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

    Mat new_image2 = Mat::zeros(image1.rows, image1.cols, CV_8UC1);
    //int filterfunc2[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    int filterfunc2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    filter(image1, filterfunc2, new_image2);

    namedWindow("image", WINDOW_AUTOSIZE);
    imshow("image", image1);

    namedWindow("New_image", WINDOW_AUTOSIZE);
    imshow("New_image", new_image2);
    waitKey();
}

void filter(Mat image, int filterfunc[3][3], Mat new_image) {
    for (int r = 1; r < image.rows - 1; r++) {
        for (int c = 1; c < image.cols - 1; c++) {
            float sum = 0;
            int i = 0, j = 0;
            for (int m = r - 1; m < r + 2; m++) {
                for (int l = c - 1; l < c + 2; l++) {
                            sum += image.at<uchar>(m, l) * filterfunc[i][j];
                            if(r == 1 && c == 1){
                                std::cout << filterfunc[m][l] << " " << i << " " << j << std::endl;
                            }
                            j++;
                }
                i++;
                j= 0;
            }
            new_image.at<uchar>(r, c) = round(sum / 16);
        }
    }
}