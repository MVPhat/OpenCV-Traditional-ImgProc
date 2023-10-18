#include "Header.h"

void filterImageGauss(int kernelSize, void* userData) {
    Mat* image = static_cast<Mat*>(userData);
    Mat filterImage;
    
    GaussianBlur(*image, filterImage, Size(kernelSize * 2 + 1, kernelSize * 2 + 1), 0, 0);

    imshow(OUTPUT_IMAGE IMAGE_TYPE_5, filterImage);
}

void filterDisplayGauss(Mat image) {
    int initKernelSize = 1, maxKernelSize = 10;

    imshow(INPUT_IMAGE, image);
    namedWindow(OUTPUT_IMAGE IMAGE_TYPE_5);
    createTrackbar("KernelSize", OUTPUT_IMAGE IMAGE_TYPE_5, &initKernelSize, maxKernelSize, filterImageGauss, (void*)&image);

    waitKey(0);
}
