#include "Header.h"

Mat calculateLBP(Mat img, int x, int y) {
    uchar center = img.at<uchar>(y, x);
    unsigned int pattern = 0;
    int count = 0;
    const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    const int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
    Mat lbpDescriptor(1, 256, CV_32F, Scalar(0));

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newY >= 0 && newX < img.cols && newY < img.rows) {
            if (img.at<uchar>(newY, newX) >= center) {
                pattern |= (1 << i);
            }
        }
    }

    lbpDescriptor.at<float>(0, pattern)++;

    return lbpDescriptor;
}

Mat computeLBP(Mat img, vector<KeyPoint> keypoints) {
    Mat grayImg;
    cvtColor(img, grayImg, COLOR_BGR2GRAY);

    vector<Mat> descriptors;

    for (const auto& kp : keypoints) {
        int x = kp.pt.x;
        int y = kp.pt.y;

        if (x > 0 && y > 0 && x < grayImg.cols - 1 && y < grayImg.rows - 1) {
            Mat lbpDesc = calculateLBP(grayImg, x, y);
            descriptors.push_back(lbpDesc);
        }
    }

    Mat lbpDescriptors;
    vconcat(descriptors, lbpDescriptors);

    return lbpDescriptors;
}

void LBP_descriptor(Mat image1, Mat image2, vector<KeyPoint> keypoints1, vector<KeyPoint> keypoints2, string detector_descriptor) {
    Mat descriptors1, descriptors2;
    descriptors1 = computeLBP(image1, keypoints1);
    descriptors2 = computeLBP(image2, keypoints2);

    vector<DMatch> goodMatches = find_good_matches(image1, image2, descriptors1, descriptors2);
    Mat imgMatches;
    drawMatches(image1, keypoints1, image2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    namedWindow(detector_descriptor);
    imshow(detector_descriptor, imgMatches);

    waitKey(0);
}