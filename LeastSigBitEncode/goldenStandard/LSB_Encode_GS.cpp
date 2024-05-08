//Image encoding LSB

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void createHeader(int length, std::string& header)
{
    // Create Header
    std::string line1 = "P3";
    std::string line2 = "#Image Test";
    std::string line3 = std::to_string(length) + " " + std::to_string(length);
    std::string line4 = "255";

    header = line1 + "\n" + line2 + "\n" + line3 + "\n" + line4;
}

void createImageData(int length, char (*imageData)[20])
{
    int inc = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            int random_r = rand() % 256;
            int random_g = rand() % 256;
            int random_b = rand() % 256;
            char pixel[20];
            sprintf(pixel, "%d\n%d\n%d\n", random_r, random_g, random_b);

            strcpy(imageData[inc], pixel);
            inc += 1;
        }
    }
}


int main()
{
    int length = 64;
    char imageData[length*length][20];

    createImageData(length, imageData);

    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    for (int i = 0; i < length*length; i++)
    {
        fileOut << imageData[i];
    }
    fileOut.close();

    return 0;
}
