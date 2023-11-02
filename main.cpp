#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

class Color {
    public:
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
        std::uint8_t alpha;
        Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a){
            red = r;
            green = g;
            blue = b;
            alpha = a;
        }
};

bool isValidColor(int value) {
    return value >= 0 && value <= 255;
}

void scanColor(std::vector<Color>& colors){
    std::regex patternDec(R"((\d{1,3}),(\d{1,3}),(\d{1,3}),(\d{1,3}))");
    std::regex patternHex(R"(^([0-9a-fA-F]{8})$)");
    std::smatch matches;
    std::ifstream txt("colors.txt");
    std::string line;
    
    while(std::getline(txt, line)){
        if (std::regex_match(line, matches, patternDec)) {
            int r = std::stoi(matches[1]);
            int g = std::stoi(matches[2]);
            int b = std::stoi(matches[3]);
            int a = std::stoi(matches[4]);
            if (isValidColor(r) && isValidColor(g) && isValidColor(b) && isValidColor(a)) {
                colors.emplace_back(r, g, b, a);
            } else {
                std::cerr << "Invalid color values: " << line << std::endl;
            }
        } else if (std::regex_match(line, matches, patternHex)) {
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
}

int main(){
    std::vector<Color> colors;
    scanColor(colors);

    for(const auto& color : colors){
        std::cout << "Red: " << static_cast<int>(color.red) << std::endl;
        std::cout << "Green: " << static_cast<int>(color.green) << std::endl;
        std::cout << "Blue: " << static_cast<int>(color.blue) << std::endl;
        std::cout << "Alpha: " << static_cast<int>(color.alpha) << std::endl;
        std::cout << std::endl;
    }
} 