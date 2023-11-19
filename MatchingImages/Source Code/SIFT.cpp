#include "Header.h"

void SIFT_descriptor(Mat image1, Mat image2, vector<KeyPoint> keypoints1, vector<KeyPoint> keypoints2, string detector_descriptor) {
    Ptr<SIFT> sift = SIFT::create();
    Mat descriptors1, descriptors2;

    sift->detectAndCompute(image1, noArray(), keypoints1, descriptors1);
    sift->detectAndCompute(image2, noArray(), keypoints2, descriptors2);
    vector<DMatch> goodMatches = find_good_matches(image1, image2, descriptors1, descriptors2);

    Mat imgMatches;
    drawMatches(image1, keypoints1, image2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    namedWindow(detector_descriptor);
    imshow(detector_descriptor, imgMatches);

    waitKey(0);
}