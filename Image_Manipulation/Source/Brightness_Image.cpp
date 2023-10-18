#include "Header.h"

void brightnessModify(int brightness, void* userData) {
	Mat brightnessImage;
	Mat* image = static_cast<Mat*>(userData);

	image->convertTo(brightnessImage, -1, 1.0, brightness);

	imshow(OUTPUT_IMAGE IMAGE_TYPE_2, brightnessImage);
}

void brightnessDisplay(Mat image) {
	int initBright = 50, maxBright = 100;

	imshow(INPUT_IMAGE, image);
	namedWindow(OUTPUT_IMAGE IMAGE_TYPE_2);
	createTrackbar("Brightness", OUTPUT_IMAGE IMAGE_TYPE_2, &initBright, maxBright, brightnessModify, (void*)&image);

	waitKey(0);
}