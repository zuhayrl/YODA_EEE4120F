#include <iostream>
#include <cstdio>
#include <ctime>

__kernel void encodeImage(__global int* image, __global int* binary, const int binarySize, const int n) {
    int i = get_global_id(0);

    // Randomly initialize the image pixels
    //uint seed = (uint)(clock() + i);
    image[i] = rand() % 256;
    //image[i] = 45;
}
