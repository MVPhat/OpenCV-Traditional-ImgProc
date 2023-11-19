#include "Header.h"

vector<KeyPoint> blob_key;

void BlobDetection(Mat inputImage) {
    SimpleBlobDetector::Params params;

    params.filterByCircularity = true;
    params.minCircularity = 0.1;
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;
    params.filterByConvexity = true;
    params.minConvexity = 0.7;
    params.filterByColor = true;
    params.blobColor = 255;
    params.minThreshold = 10;
    params.maxThreshold = 255;
    params.filterByArea = true;
    params.minArea = 300;
    params.maxArea = 1000;

    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    blob_key.clear();
    detector->detect(inputImage, blob_key);

    Mat keypointImage;
    drawKeypoints(inputImage, blob_key, keypointImage, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    namedWindow("Blob With Keypoints");
    imshow("Blob With Keypoints", keypointImage);

    waitKey(0);
}

void BlobSift(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);

    BlobDetection(image1);
    vector<KeyPoint> keypoints1 = blob_key;

    BlobDetection(image2);
    vector<KeyPoint> keypoints2 = blob_key;

    cerr << "Blob sift keypoints1 " << keypoints1.size();
    cerr << "   keypoints2 " << keypoints2.size() << "\n\n\n";

    SIFT_descriptor(image1, image2, keypoints1, keypoints2, "Blob SIFT");
}

void BlobLBP(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);

    vector<KeyPoint> keypoints1, keypoints2;

    BlobDetection(image1);
    keypoints1 = blob_key;

    BlobDetection(image2);
    keypoints2 = blob_key;

    cerr << "Blob LBP keypoints1 " << keypoints1.size();
    cerr << "   keypoints2 " << keypoints2.size() << "\n\n\n";

    LBP_descriptor(image1, image2, keypoints1, keypoints2, "Blob LBP");
}