#include <iostream>
#include "color.h"
#include "color.cpp"
#include "modes.h"
#include "modes.cpp"
#include "print.h"
#include "print.cpp"
#include "scanColor.h"
#include "scanColor.cpp"

void start(int argc, char *argv[]){
    const char* mode = "mix";
    Color resultColor;
    std::vector<Color> colors;

    if (strcmp(argv[1], "--mode") == 0 || strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "mix") == 0 || strcmp(argv[2], "lowest") == 0 || strcmp(argv[2], "highest") == 0 || strcmp(argv[2], "mix-saturate") == 0) {
            mode = argv[2];
            for(int i = 3; i < argc; i++){
                scanColorCLI(argv[i], colors);
            }
            modes(mode, resultColor, colors);
            printColor(resultColor);
        } else if (strcmp(argv[2], "") != 0){ 
            for(int i = 2; i < argc; i++){
                scanColorCLI(argv[i], colors);
            }
            modes(mode, resultColor, colors);
            printColor(resultColor);
        } else {
            fprintf(stderr, "Invalid argument for mode option.\n");
        }
    } else if (strcmp(argv[1], "-txt") == 0){
        if(argc > 2 && (strcmp(argv[2], "lowest") == 0 || strcmp(argv[2], "highest") == 0 || strcmp(argv[2], "mix-saturate") == 0)) mode = argv[2];
        scanColors(colors);
        modes(mode, resultColor, colors);
        printColor(resultColor);
    } else {
        fprintf(stderr, "Invalid command.\n");
    }
}