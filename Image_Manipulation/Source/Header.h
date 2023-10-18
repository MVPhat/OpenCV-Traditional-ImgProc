#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

#define INPUT_IMAGE "Input Image (Original)"
#define OUTPUT_IMAGE "Output Image - "
#define IMAGE_TYPE_1 "Gray Scale"
#define IMAGE_TYPE_2 "Brightness"
#define IMAGE_TYPE_3 "Contrast"
#define IMAGE_TYPE_4 "Filter Average"
#define IMAGE_TYPE_5 "Filter Gaussian"

void convert_Img_to_Grayscale(Mat image);
void brightnessModify(int brightness, void* userData);
void brightnessDisplay(Mat image);
void contrastDisplay(Mat image);
void contrastModify(int contrast, void* userData);
void filterDisplayAvg(Mat image);
void filterImageAvg(int kernelSize, void* userData);
void filterDisplayGauss(Mat image);
void filterImageGauss(int kernelSize, void* userData);