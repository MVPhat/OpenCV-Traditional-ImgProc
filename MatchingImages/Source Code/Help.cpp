#include "Header.h"

void user_guide() {	
    vector<string> guideText = {
        "\n\n========== USER GUIDE ==========",
        "1. Lab02.exe harris/blob/dog <path/to/image>",
        "2. Lab02.exe harris/blob/dog",
        "3. Lab02.exe m harris/blob/dog sift/lbp <path/to/image>",
        "4. Lab02.exe m harris/blob/dog sift/lbp",
        "5. Lab02.exe h",
        "\nExample: Lab02.exe m harris sift sample1.jpg sample2.jpg",
        "\nPress \"SPACE\" to execute the feature after calling from the command line",
        "In some situtations, you should press \"SPACE\" multiple times to ignore the modification of feature's parameters",
        "Press \"ESC\" to exit the program",
        "========== THANK YOU ==========\n\n"
    };

    for (auto i : guideText) {
        cerr << i << endl;
    }
}