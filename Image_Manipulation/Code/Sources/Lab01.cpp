#include "Header.h"

int main(int argc, char* argv[]) {
	if (argc == 3) {
		Mat image = imread(argv[2], IMREAD_UNCHANGED);
		if (image.empty()) {
			cout << "Cannot open or the path doesn't exist" << endl;
			return -1;
		}

		if (string(argv[1]) == "-rgb2gray") {
			convert_Img_to_Grayscale(image);
		}
		else if (string(argv[1]) == "-brightness") {
			brightnessDisplay(image);
		}
		else if (string(argv[1]) == "-contrast") {
			contrastDisplay(image);
		}
		else if (string(argv[1]) == "-avg") {
			filterDisplayAvg(image);
		}
		else if (string(argv[1]) == "-gauss") {
			filterDisplayGauss(image);
		}
		else {
			cout << "Error command!" << endl;
		}
	}
	else {
		cout << "Lacking of " << 3 - argc << " argument(s)!!" << endl;
		cout << "Number of arguments: " << argc << endl;
		cout << "The command line must be: Lab01.exe <Image_Manipulation> <Image_File_Path>" << endl;
		cout << "List of <Image_Manipulations>" << endl;
		cout << "1. -rgb2gray\n2. -brightness\n3. -contrast\n4. -avg\n5. -gauss\n";
	}
	return 0;
}