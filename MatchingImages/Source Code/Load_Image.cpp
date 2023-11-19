#include "Header.h"

void feature_execute(int argc, char* argv[], Mat image1, Mat image2, bool isCamera) {
    cerr << "argc = " << argc << "\n\n\n\n";
    if (argc == 2 || isCamera) {
        if (!strcmp(argv[1], "h")) {
            user_guide();
            return;
        }
        namedWindow("Input Image 1");
        namedWindow("Input Image 2");
        imshow("Input Image 1", image1);
        imshow("Input Image 2", image2);
    }
    if (argc == 2 || argc == 3) {
        if (!strcmp(argv[1], "harris")) {
            HarrisDetection(image1);
        }
        else if (!strcmp(argv[1], "blob")) {
            BlobDetection(image1);
        }
        else if (!strcmp(argv[1], "dog")) {
            DoGDetection(image1);
        }
    }
    else if (argc == 4 || argc == 6) {
        if (!strcmp(argv[2], "harris")&& !strcmp(argv[3], "sift")) {
            HarrisSift(image1, image2);
        }
        else if (!strcmp(argv[2], "blob") && !strcmp(argv[3], "sift")) {
            BlobSift(image1, image2);
        }
        else if (!strcmp(argv[2], "dog") && !strcmp(argv[3], "sift")) {
            DogSift(image1, image2);
        }
        else if (!strcmp(argv[2], "harris") && !strcmp(argv[3], "lbp")) {
            HarrisLBP(image1, image2);
        }
        else if (!strcmp(argv[2], "dog") && !strcmp(argv[3], "lbp")) {
            DoGLBP(image1, image2);
        }
        else if (!strcmp(argv[2], "blob") && !strcmp(argv[3], "lbp")) {
            BlobLBP(image1, image2);
        }
    }
}

void Load_Image(int argc, char* argv[]) {
	Mat image, image1, image2;
    VideoCapture camera;
    bool isCamera = false;
    if (argc == 2 || argc == 4) {
        camera.open(0);
        isCamera = true;
        if (!camera.isOpened()) {
            cerr << "ERROR: Could not open camera" << endl;
            return;
        }
        namedWindow("Camera", WINDOW_NORMAL);
    }
    else if (argc == 3) {
        image1 = imread(argv[2], IMREAD_UNCHANGED);
    }
    else {
        image1 = imread(argv[4], IMREAD_UNCHANGED);
        if (argc == 6) {
            image2 = imread(argv[5], IMREAD_UNCHANGED);
        }
        if (image1.empty() || image2.empty()) {
            cerr << "Could not open or read the image from file." << endl;
            return;
        }
    }
    
    while (true) {
        if (isCamera) {
            camera >> image;
            imshow("Camera", image);
        }
        else {
            if (!image1.empty()) {
                namedWindow("Input Image");
                imshow("Input Image", image1);
            }
        }
        int key = waitKey(1);
        if (key == EXIT) {
            break;
        }
        else if (key == HELP) {
            user_guide();
        }
        else if (key == 32) {
            if (isCamera) {
                if (!image.empty() && image1.empty()) {
                    image.copyTo(image1);
                }
                else {
                    image.copyTo(image2);
                }
            }
            if (((argc == 2 || argc == 3) && !image1.empty()) || (!image1.empty() && !image2.empty())) {
                feature_execute(argc, argv, image1, image2, isCamera);
            }
        }
    }
}