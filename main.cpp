#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <algorithm>
#include <iomanip>

class Color {
    public:
        int red, green, blue, alpha;
        Color(){}
        Color(int r, int g, int b, int a){
            red = r;
            green = g;
            blue = b;
            alpha = a;
        }
};

bool isValidColor(int value) {
    return value >= 0 && value <= 255;
}

void scanColorCLI(const char* values, Color& color) {
    std::regex patternDec(R"((\d{1,3}),(\d{1,3}),(\d{1,3}),(\d{1,3}))");
    std::regex patternHex(R"(^([0-9a-fA-F]{8})$)");
    std::smatch match;
    std::string s(values);

    if (std::regex_match(s, match, patternDec)) {
        if (match[1].matched) {
            int r = std::stoi(match[1]);
            int g = std::stoi(match[2]);
            int b = std::stoi(match[3]);
            int a = std::stoi(match[4]);
            if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                color.red = r;
                color.blue = b;
                color.green = g;
                color.alpha = a;
            } else {
                std::cerr << "Invalid color values: " << s << std::endl;
            }
        }
    } else if (std::regex_match(s, match, patternHex)) {
        int r = std::stoi(s.substr(0,2), nullptr, 16);
        int g = std::stoi(s.substr(2,2), nullptr, 16);
        int b = std::stoi(s.substr(4,2), nullptr, 16);
        int a = std::stoi(s.substr(6,2), nullptr, 16);
        if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
            color.red = r;
            color.blue = b;
            color.green = g;
            color.alpha = a;
        } else {
                std::cerr << "Invalid color values: " << s << std::endl;
        }
    } else {
        std::cerr << "Invalid color format: " << s << std::endl;
    }
}

void assignNewColors(int newColor, Color& color){
    color.red = newColor;
    color.blue = newColor;
    color.green = newColor;
    color.alpha = newColor;
}

void modesTxt(const char* mode, Color& color){
    int newColor;
    if (strcmp(mode, "mix") == 0){
        newColor = (color.red + color.green + color.blue + color.alpha) / 4;
        assignNewColors(newColor, color);
    } else if (strcmp(mode, "lowest") == 0) {
        newColor = std::min({color.red, color.green, color.blue, color.alpha});
        color = Color(newColor, newColor, newColor, newColor);
    } else if (strcmp(mode, "highest") == 0) {
        newColor = std::max({color.red, color.green, color.blue, color.alpha});
        color = Color(newColor, newColor, newColor, newColor);
    } else if (strcmp(mode, "mix-saturate") == 0) {

    }    
}

void printColorTxt(Color& color){
    std::cout << "Red: " << color.red << std::endl;
    std::cout << "Green: " << color.green << std::endl;
    std::cout << "Blue: " << color.blue << std::endl;
    std::cout << "Alpha: " << color.alpha << std::endl;
    std::cout << "#" 
        << std::setw(2) << std::setfill('0') << std::hex << color.red  
        << std::setw(2) << std::setfill('0') << std::hex << color.green 
        << std::setw(2) << std::setfill('0') << std::hex << color.blue 
        << std::setw(2) << std::setfill('0') << std::hex << color.alpha << std::dec << std::endl; 
    std::cout << std::endl;
}

void scanColorTxt(const char* mode, Color& color){
    std::regex patternDec(R"((\d{1,3}),(\d{1,3}),(\d{1,3}),(\d{1,3}))");
    std::regex patternHex(R"(^([0-9a-fA-F]{8})$)");
    std::smatch match;
    std::ifstream txt("colors.txt");
    std::string line;
    
    while(std::getline(txt, line)){
        if (std::regex_match(line, match, patternDec)) {
            int r = std::stoi(match[1]);
            int g = std::stoi(match[2]);
            int b = std::stoi(match[3]);
            int a = std::stoi(match[4]);
            if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                color.red = r;
                color.blue = b;
                color.green = g;
                color.alpha = a;
                modesTxt(mode, color);
                printColorTxt(color);
            } else {
                std::cerr << "Invalid color values: " << line << std::endl;
            }
        } else if (std::regex_match(line, match, patternHex)) {
            int r = std::stoi(line.substr(0,2), nullptr, 16);
            int g = std::stoi(line.substr(2,2), nullptr, 16);
            int b = std::stoi(line.substr(4,2), nullptr, 16);
            int a = std::stoi(line.substr(6,2), nullptr, 16);

            if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                color.red = r;
                color.blue = b;
                color.green = g;
                color.alpha = a;
                modesTxt(mode, color);
                printColorTxt(color);
            } else {
                std::cerr << "Invalid color values: " << line << std::endl;
            }
        }
        else {
            std::cerr << "Invalid color format: " << line << std::endl;
        }
    } 
}



void modesCLI(const char* mode, const char* values, Color& color){;
    scanColorCLI(values, color);
    int newColor;
    if (strcmp(mode, "mix") == 0){
        newColor = (color.red + color.green + color.blue + color.alpha) / 4;
        assignNewColors(newColor, color);
    } else if (strcmp(mode, "lowest") == 0) {
        newColor = std::min({color.red, color.green, color.blue, color.alpha});
        color = Color(newColor, newColor, newColor, newColor);
    } else if (strcmp(mode, "highest") == 0) {
        newColor = std::max({color.red, color.green, color.blue, color.alpha});
        color = Color(newColor, newColor, newColor, newColor);
    } else if (strcmp(mode, "mix-saturate") == 0) {

    }    
}


int main(int argc, char *argv[]){
    const char* mode = "mix";
    Color color;
    
    if (strcmp(argv[1], "--mode") == 0 || strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "mix") == 0 || strcmp(argv[2], "lowest") == 0 || strcmp(argv[2], "highest") == 0 || strcmp(argv[2], "mix-saturate") == 0) {
            modesCLI(argv[2], argv[3], color);
            std::cout << "Red: " << color.red << std::endl;
            std::cout << "Green: " << color.green << std::endl;
            std::cout << "Blue: " << color.blue << std::endl;
            std::cout << "Alpha: " << color.alpha << std::endl;
            std::cout << std::endl;
        } else if (strcmp(argv[2], "") != 0){ 
            modesCLI(mode, argv[2], color);
            std::cout << "Red: " << color.red << std::endl;
            std::cout << "Green: " << color.green << std::endl;
            std::cout << "Blue: " << color.blue << std::endl;
            std::cout << "Alpha: " << color.alpha << std::endl;
            std::cout << std::endl;
        } else {
            fprintf(stderr, "Invalid argument for mode option.\n");
            return 1;
        }
    } else if (strcmp(argv[1], "-txt") == 0){
        if(argc > 2 && (strcmp(argv[2], "lowest") == 0 || strcmp(argv[2], "highest") == 0 || strcmp(argv[2], "mix-saturate") == 0)) mode = argv[2];
        scanColorTxt(mode, color);
        std::cout << "Red: " << color.red << std::endl;
        std::cout << "Green: " << color.green << std::endl;
        std::cout << "Blue: " << color.blue << std::endl;
        std::cout << "Alpha: " << color.alpha << std::endl;
        std::cout << std::endl;
    } else {
        fprintf(stderr, "Invalid command.\n");
        return 1;
    }
} 