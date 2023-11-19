#include "Header.h"

vector<DMatch> find_good_matches(Mat image1, Mat image2, Mat descriptors1, Mat descriptors2) {
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(descriptors1, descriptors2, knnMatches, 2);

    float ratio_thresh = 0.65;
    vector<DMatch> goodMatches;
    for (int i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }
    return goodMatches;
}
