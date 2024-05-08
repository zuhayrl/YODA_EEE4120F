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

void createImageData(int length, char* imageData) 
{
    
}


int main() 
{
    int length = 64;
    

    std::ofstream fileOut("image.ppm", std::ios_base::trunc);
    fileOut << imageData;
    fileOut.close();

    return 0;
}
