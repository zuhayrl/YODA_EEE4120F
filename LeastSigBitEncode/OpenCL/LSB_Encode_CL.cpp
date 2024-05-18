//Author: Christopher Hill For the EEE4120F course at UCT
//Edited by Zuhayr Loonat

#include <stdio.h>
#include <CL/cl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <tuple>
#include <ctime>

using namespace std;

// Function to convert a string to its binary representation
void convertToBinary(const string& input, int* binary, int& size) {
    size = 0;
    for (char c : input) {
        int value = static_cast<int>(c);
        for (int i = 7; i >= 0; i--) {
            binary[size++] = (value & (1 << i)) ? 1 : 0;
        }
    }
}

int main()
{
    string username;
    cout << "Enter your username (minimum 4 characters): ";
    getline(cin, username);

    if (username.length() < 4) {
        cout << "Username must be at least 4 characters long." << endl;
        return 1;
    }

    int width = 64, height = 64;
    int imageSize = width * height;

    int binarySize;
    int binary[username.length() * 8];
    convertToBinary(username, binary, binarySize);

    int* image = new int[imageSize];

    // OpenCL initialization
    cl_uint platformCount;
    cl_platform_id *platforms;
    // get platforms count 
    clGetPlatformIDs(5, NULL, &platformCount);

    // get all platforms
    platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);
    
    //TODO: Choose platform
    cl_platform_id platform = platforms[1];

    //Outputs the information of the chosen platform
	char* Info = (char*)malloc(0x1000*sizeof(char));
	clGetPlatformInfo(platform, CL_PLATFORM_NAME      , 0x1000, Info, 0);
	//printf("Name      : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_VENDOR    , 0x1000, Info, 0);
	//printf("Vendor    : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_VERSION   , 0x1000, Info, 0);
	//printf("Version   : %s\n", Info);
	clGetPlatformInfo(platform, CL_PLATFORM_PROFILE   , 0x1000, Info, 0);
	//printf("Profile   : %s\n", Info);

    cl_device_id device; //this is your drviceID
    cl_int err;

    /* Access a device */
	//The if statement checks to see if the chosen platform uses a GPU, if not it setups the device using the CPU
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (err == CL_DEVICE_NOT_FOUND) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
    }


    //***Step 3*** creates a context that allows devices to send and receive kernels and transfer data
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);


    //***Step 4*** get details about the kernel.cl file in order to create it (read the kernel.cl file and place it in a buffer)
	//read file in
    FILE *program_handle;
    program_handle = fopen("Kernel.cl", "r");

    size_t program_size;
    fseek(program_handle, 0, SEEK_END);
    program_size = ftell(program_handle);
    rewind(program_handle);

    //sort buffer out
    char *program_buffer = (char*)malloc(program_size + 1);
    program_buffer[program_size] = '\0';
    fread(program_buffer, sizeof(char), program_size, program_handle);
    fclose(program_handle);

    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&program_buffer, &program_size, NULL);

    cl_int err3 = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    //TODO: Choose kernal
    cl_kernel kernel = clCreateKernel(program, "LSB_Encoding", &err);

    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, NULL);

    size_t global_size = imageSize;
    size_t local_size = width;

    cl_mem image_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * imageSize, image, &err);
    cl_mem binary_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * binarySize, binary, &err);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), &image_buffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &binary_buffer);
    clSetKernelArg(kernel, 2, sizeof(int), &binarySize);
    clSetKernelArg(kernel, 3, sizeof(int), &imageSize);

    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
    clFinish(queue);

    clEnqueueReadBuffer(queue, image_buffer, CL_TRUE, 0, sizeof(int) * imageSize, image, 0, NULL, NULL);

    ofstream outputFile("encoded_image.ppm");
    outputFile << "P2" << endl << width << " " << height << endl << "255" << endl;
    for (int i = 0; i < imageSize; i++) {
        outputFile << image[i] << " ";
        if ((i + 1) % width == 0) {
            outputFile << endl;
        }
    }
    outputFile.close();
    delete[] image;

    clReleaseKernel(kernel);
    clReleaseMemObject(image_buffer);
    clReleaseMemObject(binary_buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    free(platforms);
    free(Info);

    cout << "Image encoded successfully. Output file: encoded_image.ppm" << endl;

    return 0;
}
