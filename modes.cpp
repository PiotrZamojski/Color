#include "modes.h"

void mixColor(Color& color, const std::vector<Color>& colors) {
    int totalRed = 0, totalGreen = 0,  totalBlue = 0, totalAlpha = 0;
    
    for (const auto& color : colors) {
        totalRed += color.red;
        totalGreen += color.green;
        totalBlue += color.blue;
        totalAlpha += color.alpha;
    }
    color.red = totalRed / colors.size();
    color.green = totalGreen / colors.size();
    color.blue = totalBlue / colors.size();
    color.alpha = totalAlpha / colors.size();
}

void setLowest(Color& color, std::vector<Color>& colors) {
    auto minRedColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.red < b.red;});
    auto minGreenColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.green < b.green;});
    auto minBlueColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.blue < b.blue;});
    auto minAlphaColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.alpha < b.alpha;});
    color.red = minRedColor->red;
    color.green = minGreenColor->green;
    color.blue = minBlueColor->blue;
    color.alpha = minAlphaColor->alpha;
}

void setHighest(Color& color, std::vector<Color>& colors){
    auto maxRedColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.red > b.red;});
    auto maxGreenColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.green > b.green;});
    auto maxBlueColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
        return a.blue > b.blue;});
    auto maxAlphaColor = std::min_element(colors.begin(), colors.end(), [](const Color& a, const Color& b) {
         return a.alpha > b.alpha;});
    color.red = maxRedColor->red;
    color.green = maxGreenColor->green;
    color.blue = maxBlueColor->blue;
    color.alpha = maxAlphaColor->alpha;
}

void setMixSaturate(Color& color, std::vector<Color>& colors) {
    double r = colors.back().red / 255.0;
    double g = colors.back().green / 255.0;
    double b = colors.back().blue / 255.0;
    double maxValue = std::max({r, g, b});
    double minValue = std::min({r, g, b});
    double diff = maxValue - minValue;

    int hue = 0;
    double lightness = 0;
    double saturation = 0;
    double totalSaturation = 0;
    double averageSaturation = 0;

    if (diff != 0) {
        if (maxValue == r) {
            hue = 60 * fmod((g - b), 6) / diff;
        } else if (maxValue == g) {
            hue = 60 * ((b - r) / diff + 2);
        } else if (maxValue == b) {
            hue = 60 * ((r - g) / diff + 4);
        }
    }

    lightness = (maxValue + minValue) / 2;

    for(int i = 0; i < colors.size()-1; i++){
        totalSaturation += colors[i].calculateSaturation();
    }

    if (!colors.empty()) {
        averageSaturation = totalSaturation / (colors.size()-1);
    }

    color.red = colors.back().red;
    color.green = colors.back().green;
    color.blue = colors.back().blue;
    color.alpha = colors.back().alpha;
    color.hue = abs(hue);
    color.lightness = lightness;
    color.saturation = averageSaturation;
}

void calculateHSL(Color& color) {
    double r = color.red / 255.0;
    double g = color.green / 255.0;
    double b = color.blue / 255.0;
    double maxValue = std::max({r, g, b});
    double minValue = std::min({r, g, b});
    double diff = maxValue - minValue;

    int hue = 0;
    double lightness = 0;
    double saturation = 0;

    if (diff != 0) {
        if (maxValue == r) {
            hue = 60 * fmod((g - b), 6) / diff;
        } else if (maxValue == g) {
            hue = 60 * ((b - r) / diff + 2);
        } else if (maxValue == b) {
            hue = 60 * ((r - g) / diff + 4);
        }
    }

    lightness = (maxValue + minValue) / 2;
    if(diff == 0) saturation = 0;
    else {
        saturation = diff / (1 - fabs(2 * lightness - 1.0));
    }

    color.hue = abs(hue);
    color.lightness = lightness;
    color.saturation = saturation;
}

void modes(const char* mode, Color& color, std::vector<Color>& colors){
    if (strcmp(mode, "mix") == 0){
        mixColor(color, colors);
        calculateHSL(color);
    } else if (strcmp(mode, "lowest") == 0) {
        setLowest(color, colors);
        calculateHSL(color);
    } else if (strcmp(mode, "highest") == 0) {
        setHighest(color, colors);
        calculateHSL(color);
    } else if (strcmp(mode, "mix-saturate") == 0) {
        setMixSaturate(color, colors);
    }    
}