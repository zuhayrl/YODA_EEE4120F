__kernel void LSB_Decoding(__global const int* image, __global int* binary, const int imageSize) {
    int i = get_global_id(0);
    int j = get_group_id(0);

    if (i == (j*64+63)) {
        binary[j] = image[i] & 1;
    }
}
