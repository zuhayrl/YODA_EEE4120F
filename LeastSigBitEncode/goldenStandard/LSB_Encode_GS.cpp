/**********************************************************************
 * Program that creates random RGB values for a 64x64 px image
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void createImage(int length, string imageData)
{
    //Create Header
    string line1 = "P3";
    string line2 = "#Image Test";
    string line3 = to_string(length) + " " + to_string(length);
    string line4 = "255";

    imageData = line1 +"\n"+ line2 +"\n" + line3 + "\n" + line4;
    //Create Pixels
    for (int i=0; i<length; i++)
    {
        for (int j=0; j<length; j++)
        {
            int random_r = rand()%256;
            int random_g = rand()%256;
            int random_b = rand()%256;
            imageData = imageData + "\n" + to_string(random_r) +"\n" + to_string(random_g) +"\n"+ to_string(random_b);
        }
    }

}

int main()
{
    string imageData = "";
    int length = 64;
    createImage(length, imageData);

    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    fileOut << imageData;

    return 0;
}
