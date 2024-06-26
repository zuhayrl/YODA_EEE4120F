#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring> // for strcpy and strcat

using namespace std;

void createImage(int length, char* line) 
{
    // Create Header
    char line1[] = "P3\n";
    char line2[] = "#Image Test\n";
    char line3[20];
    sprintf(line3, "%d %d\n", length, length);
    char line4[] = "255\n";

    strcpy(line, line1);
    strcat(line, line2);
    strcat(line, line3);
    strcat(line, line4);

    // Create Pixels
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int random_r = rand() % 256;
            int random_g = rand() % 256;
            int random_b = rand() % 256;
            char pixel[20];
            sprintf(pixel, "%d\n%d\n%d\n", random_r, random_g, random_b);
            strcat(line, pixel);
        }
    }
}

int main() 
{
    char imageData[100000]; // Adjust the size according to your requirement
    int length = 64;
    createImage(length, imageData);

    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    fileOut << imageData;
    fileOut.close();

    return 0;
}
