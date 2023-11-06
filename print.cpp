#include "print.h"

void printColor(Color& color){
    std::cout << "Red: " << color.red << std::endl;
    std::cout << "Green: " << color.green << std::endl;
    std::cout << "Blue: " << color.blue << std::endl;
    std::cout << "Alpha: " << color.alpha << std::endl;
    std::cout << "#" 
        << std::setw(2) << std::setfill('0') << std::hex << color.red  
        << std::setw(2) << std::setfill('0') << std::hex << color.green 
        << std::setw(2) << std::setfill('0') << std::hex << color.blue 
        << std::setw(2) << std::setfill('0') << std::hex << color.alpha << std::dec << std::endl; 
    std::cout << "HUE: " << color.hue << std::endl;
    std::cout << "Saturation: " << color.saturation << std::endl;
    std::cout << "Lightness: " << color.lightness << std::endl;
}