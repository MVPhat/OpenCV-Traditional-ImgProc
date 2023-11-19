#include "Header.h"

int main(int argc, char* argv[]) {
    if (argc == 2 && !strcmp(argv[1], "h")) {
        user_guide();
    }
    else Load_Image(argc, argv);

    return 0;
}