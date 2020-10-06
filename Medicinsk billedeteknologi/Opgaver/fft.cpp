#include "fft.h"



void runFFT(const std::string& filename) {
   // A gray image
   cv::Mat_<float> img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
   
   cv::Mat padded;                            //expand input image to optimal size
   int m = cv::getOptimalDFTSize( img.rows );
   int n = cv::getOptimalDFTSize( img.cols ); // on the border add zero values
   copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    
   cv::Mat_<float> imgs[] = {padded.clone(), cv::Mat_<float>(padded.rows, padded.cols, 0.0f)};
   
   // Merge
   cv::Mat_<cv::Vec2f> img_dft;
   cv::merge(imgs, 2, img_dft);
   
   // Compute DFT
   cv::dft(img_dft, img_dft);
   
   // Split
   cv::split(img_dft, imgs);
   
   // Compute magnitude/phase
   cv::Mat_<float> magnitude, phase;
   cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);
   
   // Shift quadrants for viewability
   dftshift(magnitude);
   
   // Logarithm of magnitude
   cv::Mat_<float> magnitudel;
   
   // Output image for HPF
   cv::Mat_<float> imgout; 
   
   // Take logarithm of magnitude
   magnitudel = magnitude + 1.0f;
   cv::log(magnitudel, magnitudel);
   
   // Show
   cv::normalize(img, img, 0.0, 1.0, cv::NORM_MINMAX);
   cv::normalize(magnitudel, magnitudel, 0.0, 1.0, cv::NORM_MINMAX);
   cv::normalize(phase, phase, 0.0, 1.0, cv::NORM_MINMAX);
   cv::imshow("Input", img);
   cv::imshow("Magnitude", magnitudel);
   cv::waitKey();
}

void dftshift(cv::Mat &magnitude) {
   const int cx = magnitude.cols/2;
   const int cy = magnitude.rows/2;
   
   cv::Mat_<float> tmp;
   cv::Mat_<float> topLeft(magnitude, cv::Rect(0, 0, cx, cy));
   cv::Mat_<float> topRight(magnitude, cv::Rect(cx, 0, cx, cy));
   cv::Mat_<float> bottomLeft(magnitude, cv::Rect(0, cy, cx, cy));
   cv::Mat_<float> bottomRight(magnitude, cv::Rect(cx, cy, cx, cy));
   
   topLeft.copyTo(tmp);
   bottomRight.copyTo(topLeft);
   tmp.copyTo(bottomRight);
   
   topRight.copyTo(tmp);
   bottomLeft.copyTo(topRight);
   tmp.copyTo(bottomLeft);
}

void inverseDFT(const std::string& filename) {

    // A gray image
    cv::Mat_<float> img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    cv::Rect origSize(0, 0, img.cols, img.rows);

    cv::Mat padded; // expand input image to optimal size
    int m = cv::getOptimalDFTSize(2 * img.rows);
    int n = cv::getOptimalDFTSize(2 * img.cols); // on the border add zero values
    copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols,
        cv::BORDER_CONSTANT, cv::Scalar::all(0));

    cv::Mat_<float> imgs[] = { padded.clone(),
                              cv::Mat_<float>(padded.rows, padded.cols, 0.0f) };

    // Merge
    cv::Mat_<cv::Vec2f> img_dft;
    cv::merge(imgs, 2, img_dft);

    // Compute DFT
    cv::dft(img_dft, img_dft);

    // Split
    cv::split(img_dft, imgs);

    // Compute magnitude/phase
    cv::Mat_<float> magnitude, phase;
    cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);

    // Shift quadrants for viewability
    dftshift(magnitude);

    cv::Mat_<float> orig_magnitudel = magnitude + 1.0f;
    cv::log(orig_magnitudel, orig_magnitudel);

    // Output image
    cv::Mat_<float> imgout;

    // // ILP
    float halfOfSmallestImageSide = std::min(img_dft.rows, img_dft.cols) / 2.0;
    float D0 = 0.3; // cutoff frequency as decimal percentage of new (optimal) image size
    int fS = halfOfSmallestImageSide * D0;
    cv::Mat filter(img_dft.rows, img_dft.cols, img_dft.type(),
        cv::Scalar(0.0, 0.0));
    filter(cv::Rect(filter.cols / 2 - fS, filter.rows / 2 - fS, fS * 2.0, fS * 2.0)) =
        cv::Scalar(1.0, 0.0);

    // IHP
//    float halfOfSmallestImageSide = std::min(img_dft.rows, img_dft.cols) / 2.0;
//    float D0 = 0.3; // cutoff frequency as decimal percentage of new (optimal) image size
//    int fS = halfOfSmallestImageSide * D0;
//    cv::Mat filter(img_dft.rows, img_dft.cols, img_dft.type(),
//                   cv::Scalar(1.0, 0.0));
//    filter(cv::Rect(filter.cols / 2 - fS, filter.rows / 2 - fS, fS * 2.0, fS * 2.0)) =
//            cv::Scalar(0.0, 0.0);

    // // GLP
//    float halfOfSmallestImageSide = std::min(img_dft.rows, img_dft.cols) / 2.0;
//    float D0 = 0.1; // cutoff frequency as decimal percentage of new (optimal) image size
//    float fS = D0 * halfOfSmallestImageSide;
//    cv::Mat filter(img_dft.rows, img_dft.cols, img_dft.type());
//    {
//        cv::Vec2f *p;
//        const int cu = filter.cols / 2;
//        const int cv = filter.rows / 2;
//
//        for (int i = 0; i < filter.rows; ++i) {
//            p = filter.ptr<cv::Vec2f>(i);
//            for (int j = 0; j < filter.cols; ++j) {
//                int u = cu - j;
//                int v = cv - i;
//                p[j] = cv::Vec2f((float)exp(-1.0 * sqrt(u * u + v * v) / fS), 0.0f);
//            }
//        }
//    }

    cv::split(filter, imgs);
    cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);
    cv::imshow("Filter", magnitude);


    dftshift(filter);

    cv::mulSpectrums(img_dft, filter, img_dft, 0);
    cv::split(img_dft, imgs);
    cv::cartToPolar(imgs[0], imgs[1], magnitude, phase);

    cv::Mat_<float> final_magnitudel;
    final_magnitudel = magnitude + 1.0f;
    dftshift(final_magnitudel);
    cv::log(final_magnitudel, final_magnitudel);

    // Do inverse DFT
    cv::dft(img_dft, imgout,
        cv::DFT_INVERSE + cv::DFT_SCALE + cv::DFT_REAL_OUTPUT);

    // Show
    cv::normalize(img, img, 0.0, 1.0, cv::NORM_MINMAX);
    cv::normalize(orig_magnitudel, orig_magnitudel, 0.0, 1.0, cv::NORM_MINMAX);
    cv::normalize(final_magnitudel, final_magnitudel, 0.0, 1.0, cv::NORM_MINMAX);
    cv::normalize(phase, phase, 0.0, 1.0, cv::NORM_MINMAX);
    cv::imshow("Input", img);
    cv::imshow("Original magnitude", orig_magnitudel);

    cv::imshow("New magnitude", final_magnitudel);

    imgout = imgout(origSize);
    cv::normalize(imgout, imgout, 0.0, 1.0, cv::NORM_MINMAX);
    cv::imshow("Output", imgout);
    cv::waitKey();
    cv::normalize(orig_magnitudel, orig_magnitudel, 0.0, 255.0, cv::NORM_MINMAX);
}
