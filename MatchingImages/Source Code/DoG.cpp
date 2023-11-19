#include "Header.h"

struct DogParams {
    Mat* image, *original;
    int ksize1, ksize2, sigma1, sigma2, thresh;
};

Mat dog_result;
DogParams dogParams;
vector<KeyPoint> dog_key;

void DoGModify(int, void* userData) {
    DogParams* params = static_cast<DogParams*>(userData);
    Mat* image = params->image;
    int ksize1 = params->ksize1;
    int ksize2 = params->ksize2;
    int sigma1 = params->sigma1;
    int sigma2 = params->sigma2;

    ksize1 = (ksize1 % 2 == 0) ? ksize1 + 1 : ksize1;
    ksize2 = (ksize2 % 2 == 0) ? ksize2 + 1 : ksize2;

    Mat gaussian1, gaussian2;
    GaussianBlur(*image, gaussian1, Size(ksize1, ksize1), sigma1, sigma1);
    GaussianBlur(*image, gaussian2, Size(ksize2, ksize2), sigma2, sigma2);

    dog_result = gaussian1 - gaussian2;

    Ptr<FastFeatureDetector> orb = FastFeatureDetector::create(params->thresh);
    dog_key.clear();
    orb->detect(dog_result, dog_key);
    
    namedWindow("DoG With Keypoints");
    Mat keypointImage;
    drawKeypoints(*params->original, dog_key, keypointImage, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("DoG With Keypoints", keypointImage);
}

void DoGDetection(Mat inputImage) {
    dogParams.image = dogParams.original = &inputImage;
    dogParams.ksize1 = 3;
    dogParams.ksize2 = 7;
    dogParams.sigma1 = 1;
    dogParams.sigma2 = 2;
    dogParams.thresh = 40;
   
    namedWindow("TrackBar");
    createTrackbar("Kernel Size 1", "TrackBar", &dogParams.ksize1, 21, DoGModify, &dogParams);
    createTrackbar("Kernel Size 2", "TrackBar", &dogParams.ksize2, 21, DoGModify, &dogParams);
    createTrackbar("Sigma 1", "TrackBar", &dogParams.sigma1, 10, DoGModify, &dogParams);
    createTrackbar("Sigma 2", "TrackBar", &dogParams.sigma2, 10, DoGModify, &dogParams);
    createTrackbar("Threshold", "TrackBar", &dogParams.thresh, 255, DoGModify, &dogParams);

    DoGModify(0, &dogParams);

    waitKey(0);
}

void DogSift(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);

    DoGDetection(image1);
    vector<KeyPoint> keypoints1 = dog_key;

    DoGDetection(image2);
    vector<KeyPoint> keypoints2 = dog_key;

    SIFT_descriptor(image1, image2, keypoints1, keypoints2, "DoG SIFT");
}

void DoGLBP(Mat image1, Mat image2) {
    namedWindow("Input Image 2");
    imshow("Input Image 2", image2);

    vector<KeyPoint> keypoints1, keypoints2;

    DoGDetection(image1);
    keypoints1 = dog_key;

    DoGDetection(image2);
    keypoints2 = dog_key;

    LBP_descriptor(image1, image2, keypoints1, keypoints2, "DoG LBP");
}