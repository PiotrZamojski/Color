#include "scanColor.h"

bool isValidColor(int value) {
    return value >= 0 && value <= 255;
}

void scanColorCLI(const char* values, std::vector<Color>& colors) {
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
                colors.emplace_back(r, b, g, a);
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
            colors.emplace_back(r, b, g, a);
        } else {
                std::cerr << "Invalid color values: " << s << std::endl;
        }
    } else {
        std::cerr << "Invalid color format: " << s << std::endl;
    }
}

void scanColors(std::vector<Color>& colors){
    std::regex patternDec(R"((\d{1,3}),(\d{1,3}),(\d{1,3}),(\d{1,3}))");
    std::regex patternHex(R"(^([0-9a-fA-F]{8})$)");
    std::smatch match;
    std::ifstream txt("colors.txt");
    std::string line;

    if (txt.is_open()) {
        while(std::getline(txt, line)){
            if (std::regex_match(line, match, patternDec)) {
                int r = std::stoi(match[1]);
                int g = std::stoi(match[2]);
                int b = std::stoi(match[3]);
                int a = std::stoi(match[4]);
                if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                    colors.emplace_back(r, g, b, a);
                } else {
                    std::cerr << "Invalid color values: " << line << std::endl;
                }
            } else if (std::regex_match(line, match, patternHex)) {
                int r = std::stoi(line.substr(0,2), nullptr, 16);
                int g = std::stoi(line.substr(2,2), nullptr, 16);
                int b = std::stoi(line.substr(4,2), nullptr, 16);
                int a = std::stoi(line.substr(6,2), nullptr, 16);

                if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                    colors.emplace_back(r, g, b, a);
                } else {
                    std::cerr << "Invalid color values: " << line << std::endl;
                }
            }
            else {
                std::cerr << "Invalid color format: " << line << std::endl;
            }
        } 
        txt.close();
    } else {
        std::cerr << "Error: Unable to open 'colors.txt' file." << std::endl;
    }
}