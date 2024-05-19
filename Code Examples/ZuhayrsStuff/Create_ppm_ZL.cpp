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
    std::string line2 = "#Image GS";
    std::string line3 = std::to_string(length) + " " + std::to_string(length);
    std::string line4 = "255";

    header = line1 + "\n" + line2 + "\n" + line3 + "\n" + line4 + "\n";
}

void createImageData(int length, char (*imageData)[20])
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            int random_r = rand() % 256;
            int random_g = rand() % 256;
            int random_b = rand() % 256;
            char pixel[20];
            sprintf(pixel, "%d\n%d\n%d\n", random_r, random_g, random_b);

            strcpy(imageData[i*length+j], pixel);
        }
    }
}


int main()
{
    int length = 64;
    char imageData[length*length][20];
    std::string header;

    createHeader(length, header);
    createImageData(length, imageData);

    //output header
    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    fileOut << header;

    for (int i = 0; i < length*length; i++)
    {
        fileOut << imageData[i];
    }
    fileOut.close();

    return 0;
}
