#include "Header.h"

void contrastModify(int contrast, void* userData) {
	Mat* image = static_cast<Mat*>(userData);
	Mat contrastImage;

	image->convertTo(contrastImage, -1, contrast / 50.0, 0);

	imshow(OUTPUT_IMAGE IMAGE_TYPE_3, contrastImage);
}

void contrastDisplay(Mat image) {
	int initContrast = 10, maxContrast = 100;

	imshow(INPUT_IMAGE, image);
	namedWindow(OUTPUT_IMAGE IMAGE_TYPE_3);
	createTrackbar("Contrast", OUTPUT_IMAGE IMAGE_TYPE_3, &initContrast, maxContrast, contrastModify, (void*)&image);

	waitKey(0);
}