#include "Header.h"

void convert_Img_to_Grayscale(Mat image) {
	Mat grayImage;

	cvtColor(image, grayImage, COLOR_RGB2GRAY);
	imshow(INPUT_IMAGE, image);
	imshow(OUTPUT_IMAGE IMAGE_TYPE_1, grayImage);

	// cout << "Number of channels: " << grayImage.channels() << endl;
	// vector<int> compress_params = { IMWRITE_PNG_COMPRESSION, 0 };
	// imwrite("gc.png", grayImage, compress_params);

	waitKey(0);
}