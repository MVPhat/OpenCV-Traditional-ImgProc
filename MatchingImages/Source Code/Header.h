#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

#define EXIT 27
#define HELP 104

void Load_Image(int, char*[]);

void HarrisDetection(Mat);
void BlobDetection(Mat);
void DoGDetection(Mat);
void HarrisSift(Mat, Mat);
void BlobSift(Mat, Mat);
void DogSift(Mat, Mat);
void HarrisLBP(Mat, Mat);
void BlobLBP(Mat, Mat);
void DoGLBP(Mat, Mat);
void SIFT_descriptor(Mat, Mat, vector<KeyPoint>, vector<KeyPoint>, string);
vector<DMatch> find_good_matches(Mat, Mat, Mat, Mat);

void LBP_descriptor(Mat, Mat, vector<KeyPoint>, vector<KeyPoint>, string);

void user_guide();