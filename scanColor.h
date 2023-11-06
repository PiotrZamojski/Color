#ifndef SCANCOLOR_H
#define SCANCOLOR_H
#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include "color.H"

bool isValidColor(int value);
void scanColorCLI(const char* values, std::vector<Color>& colors);
void scanColors(std::vector<Color>& colors);

#endif