__kernel void decodeImage(__global int* image, __global int* binary, const int binSize, const int n) {
    
    int binaryIndex = get_global_id(0);

    if (binaryIndex < binSize) {
        binary[binaryIndex] = image[binaryIndex * n] & 1;
        //printf("Bin %d: %d \n",binaryIndex , binary[binaryIndex]);
    }

}
