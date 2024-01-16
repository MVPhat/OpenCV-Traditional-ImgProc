#include "Header.h"

void filterImageAvg(int kernelSize, void* userData) {
    Mat* image = static_cast<Mat*>(userData);
    Mat filterImage;
    if (kernelSize == 0) return;

    if (image->channels() == 1) {
        // Grayscale
        Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
        filter2D(*image, filterImage, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    }
    else {
        // Color image
        vector<Mat> channels;
        split(*image, channels);

        for (int i = 0; i < 3; i++) {
            Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
            filter2D(channels[i], channels[i], -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
        }

        merge(channels, filterImage);
    }

    imshow(OUTPUT_IMAGE IMAGE_TYPE_4, filterImage);
}

void filterDisplayAvg(Mat image) {
    int initKernelSize = 1, maxKernelSize = 10;

    // cout << "Number of channels: " << image.channels() << endl;

    imshow(INPUT_IMAGE, image);
    namedWindow(OUTPUT_IMAGE IMAGE_TYPE_4);
    createTrackbar("KernelSize", OUTPUT_IMAGE IMAGE_TYPE_4, &initKernelSize, maxKernelSize, filterImageAvg, (void*)&image);

    waitKey(0);
}