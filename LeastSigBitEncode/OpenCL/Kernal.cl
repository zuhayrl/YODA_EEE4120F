__kernel void LSB_Encoding(__global int* image, __global int* binary, const int binarySize, const int imageSize) {
    int i = get_global_id(0);

    // Randomly initialize the image pixels
    uint seed = (uint)(clock() + i);
    image[i] = seed % 256;

    // Perform LSB encoding if within the binary size
    if (i < binarySize) {
        image[i] = (image[i] & ~1) | binary[i];
    }
}
