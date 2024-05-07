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

int main()
{
    string line1 = "P3";
    string line2 = "#Image 1";
    string line3 = "64 64";
    string line4 = "255";
    string rgb_val = line1 +"\n"+ line2 +"\n" + line3 + "\n" + line4 + "\n";
    for (int i=0; i<64; i++)
    {
        for (int j=0; j<64; j++)
        {
            if (i == 63 && j == 63)
            {
                int random_r = rand()%256;
                int random_g = rand()%256;
                int random_b = rand()%256;
                rgb_val = rgb_val + to_string(random_r) +"\n" + to_string(random_g) +"\n"+ to_string(random_b);
            }
            else
            {
                int random_r = rand()%256;
                int random_g = rand()%256;
                int random_b = rand()%256;
                rgb_val = rgb_val + to_string(random_r) +"\n" + to_string(random_g) +"\n"+ to_string(random_b) + "\n";
            }
        }
    }
    std::ofstream fileOut;
    fileOut.open("image.ppm", std::ios_base::app);
    fileOut<<rgb_val;
    return 0;
}
