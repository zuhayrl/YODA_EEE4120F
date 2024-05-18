#include <iostream>
#include <CL/cl.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to convert binary representation to a string
string convertFromBinary(const vector<int>& binary) {
    string output;
    int size = binary.size();
    for (int i = 0; i < size; i += 8) {
        int value = 0;
        for (int j = 0; j < 8; ++j) {
            value = (value << 1) | binary[i + j];
        }
        output += static_cast<char>(value);
    }
    return output;
}

// Function to decode the binary data from the image using LSB encoding
void decodeImage(const vector<int>& image, int n, int binarySize, vector<int>& binary) {
    int binaryIndex = 0;
    for (int i = 0; i < image.size(); i += n) {
        if (binaryIndex >= binarySize) {
            break;
        }
        binary[binaryIndex++] = image[i] & 1;
    }
}

int main() {
    string username, imageName;
    cout << "Enter your username: ";
    getline(cin, username);

    cout << "Enter the image filename: ";
    getline(cin, imageName);

    // Read the encoded image from the PPM file
    ifstream inputFile(imageName);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << imageName << endl;
        return 1;
    }

    string format;
    int width, height, maxVal;
    inputFile >> format >> width >> height >> maxVal;

    int imageSize = width * height;
    vector<int> image(imageSize);

    for (int i = 0; i < imageSize; i++) {
        inputFile >> image[i];
    }
    inputFile.close();

    int binarySize = username.length() * 8;
    vector<int> binary(binarySize);

    // OpenCL code begins here
    // Step 1: Initialize OpenCL structures and buffers
    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

    // Step 2: Get the platform and device
    err = clGetPlatformIDs(1, &platform, NULL);
    err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error getting platform or device." << endl;
        return 1;
    }

    // Step 3: Create a context
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        cout << "Error creating context." << endl;
        return 1;
    }

    // Step 4: Read the kernel file
    ifstream kernelFile("Kernel.cl");
    if (!kernelFile.is_open()) {
        cout << "Error opening kernel file." << endl;
        return 1;
    }
    string kernelSource((istreambuf_iterator<char>(kernelFile)), istreambuf_iterator<char>());
    kernelFile.close();
    const char* kernelSourcePtr = kernelSource.c_str();
    size_t kernelSize = kernelSource.length();

    // Step 5: Create a program from the source
    program = clCreateProgramWithSource(context, 1, &kernelSourcePtr, &kernelSize, &err);
    if (err != CL_SUCCESS) {
        cout << "Error creating program." << endl;
        return 1;
    }

    // Step 6: Build the program
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error building program." << endl;
        return 1;
    }

    // Step 7: Create the kernel
    kernel = clCreateKernel(program, "LSB_Decoding", &err);
    if (err != CL_SUCCESS) {
        cout << "Error creating kernel." << endl;
        return 1;
    }

    // Step 8: Create a command queue
    queue = clCreateCommandQueue(context, device, 0, &err);
    if (err != CL_SUCCESS) {
        cout << "Error creating command queue." << endl;
        return 1;
    }

    // Step 9: Create data buffers
    cl_mem imageBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * imageSize, image.data(), &err);
    cl_mem binaryBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * binarySize, NULL, &err);

    // Step 10: Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &imageBuffer);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &binaryBuffer);
    err |= clSetKernelArg(kernel, 2, sizeof(int), &imageSize);
    if (err != CL_SUCCESS) {
        cout << "Error setting kernel arguments." << endl;
        return 1;
    }

    // Step 11: Enqueue the kernel
    size_t globalSize = imageSize;
    size_t local_size = width;

    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, NULL, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error enqueueing kernel." << endl;
        return 1;
    }

    // Step 12: Read output buffer
    err = clEnqueueReadBuffer(queue, binaryBuffer, CL_TRUE, 0, sizeof(int) * binarySize, binary.data(), 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cout << "Error reading buffer." << endl;
        return 1;
    }

    // Step 13: Cleanup
    clReleaseMemObject(imageBuffer);
    clReleaseMemObject(binaryBuffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    // Step 14: Decode binary data
    string decodedUsername = convertFromBinary(binary);

    cout << "Decoded username from image: " << decodedUsername << endl;

    if (username == decodedUsername) {
        cout << "Username matches the encoded image." << endl;
    } else {
        cout << "Username does not match the encoded image." << endl;
    }

    return 0;
}
