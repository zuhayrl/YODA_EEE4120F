//Create encoded image

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void createImage(int length, std::string& line) 
{
    // Create Header
    std::string line1 = "P3";
    std::string line2 = "#Image Test";
    std::string line3 = std::to_string(length) + " " + std::to_string(length);
    std::string line4 = "255";

    line = line1 + "\n" + line2 + "\n" + line3 + "\n" + line4;

    // Create Pixels
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int random_r = rand() % 256;
            int random_g = rand() % 256;
            int random_b = rand() % 256;
            line += "\n" + std::to_string(random_r) + "\n" + std::to_string(random_g) + "\n" + std::to_string(random_b);
        }
    }
}

int main() 
{
    std::string imageData;
    int length = 64;
    createImage(length, imageData);
    //std::cout << imageData << std::endl;

    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    fileOut << imageData;

    return 0;
}
