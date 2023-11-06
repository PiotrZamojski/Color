#ifndef MODES_H
#define MODES_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "color.h"

void mixColor(Color& color, const std::vector<Color>& colors);
void setLowest(Color& color, std::vector<Color>& colors);
void setHighest(Color& color, std::vector<Color>& colors);
void setMixSaturate(Color& color, std::vector<Color>& colors);
void calculateHSL(Color& color);
void modes(const char* mode, Color& color, std::vector<Color>& colors);

#endif