#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Color {
    public:
        int red, green, blue, alpha, hue = 0;
        double  saturation = 0, lightness = 0;
        Color();
        Color(int r, int g, int b, int a);
        double calculateSaturation() const;
};

#endif