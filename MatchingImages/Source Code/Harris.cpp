#include "Header.h"

vector<KeyPoint> harris_key;
struct HarrisParams {
    Mat* image, *original;
    int blockSize, apertureSize, thresh;
};

HarrisParams harrisParams;

void cornerHarrisModify(int, void* userData) {
    HarrisParams* params = static_cast<HarrisParams*>(userData);
    int blockSize = params->blockSize;
    int apertureSize = (params->apertureSize % 2 == 0) ? params->apertureSize + 1 : params->apertureSize;
    double k = 0.04;
    int thresh = params->thresh;
    Mat* image = params->image;
    Mat dst = Mat::zeros(params->image->size(), CV_32FC1);
    Mat dst_norm, dst_norm_scaled;

    cornerHarris(*image, dst, blockSize, apertureSize, k);
    
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    harris_key.clear();
    for (int i = 0; i < dst_norm.rows; i++) {
        for (int j = 0; j < dst_norm.cols; j++) {
            if ((int)dst_norm.at<float>(i, j) > thresh) {
                circle(dst_norm_scaled, Point(j, i), 5, Scalar(0, 0, 255), 2, 8, 0);
                harris_key.push_back(KeyPoint(j, i, 1));
            }
        }
    }
    Mat keypointImage;
    drawKeypoints(*params->original, harris_key, keypointImage, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("Harris With Keypoints", keypointImage);
    imshow("Harris", dst_norm_scaled);
}

void HarrisDetection(Mat inputImage) {
    Mat grayImage, keypointImage;
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);

    harrisParams.blockSize = 2;
    harrisParams.apertureSize = 3;
    harrisParams.thresh = 150;
    harrisParams.image = &grayImage;
    harrisParams.original = &inputImage;
    
    namedWindow("Harris");
    namedWindow("TrackBar");
    
    createTrackbar("Block Size", "TrackBar", &harrisParams.blockSize, 10, cornerHarrisModify, &harrisParams);
    createTrackbar("Aperture Size", "TrackBar", &harrisParams.apertureSize, 10, cornerHarrisModify, &harrisParams);
    createTrackbar("Threshold", "TrackBar", &harrisParams.thresh, 255, cornerHarrisModify, &harrisParams);
    cornerHarrisModify(0, &harrisParams);
    waitKey(0);
}

void HarrisSift(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);
    vector<KeyPoint> keypoints1, keypoints2;

    HarrisDetection(image1);
    keypoints1 = harris_key;

    HarrisDetection(image2);
    keypoints2 = harris_key;

    SIFT_descriptor(image1, image2, keypoints1, keypoints2, "Harris SIFT");
}

void HarrisLBP(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);

    vector<KeyPoint> keypoints1, keypoints2;

    HarrisDetection(image1);
    keypoints1 = harris_key;

    HarrisDetection(image2);
    keypoints2 = harris_key;

    LBP_descriptor(image1, image2, keypoints1, keypoints2, "Harris LBP");
}