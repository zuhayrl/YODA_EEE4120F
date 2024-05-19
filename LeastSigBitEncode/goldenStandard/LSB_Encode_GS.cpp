#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
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

// Function to encode the binary data into the image using LSB encoding
void encodeImage(int* image, int* binary, int binarySize, int n, int imageSize) {
    int binaryIndex = 0;
    for (int i = 0; i < imageSize; i += n) {
        if (binaryIndex >= binarySize) {
            break;
        }
        image[i] = (image[i] & ~1) | binary[binaryIndex++];
    }
}

int main() {
    string username;
    cout << "Enter your username (minimum 4 characters): ";
    getline(cin, username);

    if (username.length() < 4) {
        cout << "Username must be at least 4 characters long." << endl;
        return 1;
    }

    int width = 64, height = 64;
    int imageSize = width * height;
    int* image = new int[imageSize];
    int* imageNon = new int[imageSize]; //for comparison

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize image with random pixels
    for (int i = 0; i < imageSize; i++) {
        image[i] = rand() % 256; // Random value between 0 and 255
        imageNon[i] = image[i]; //for comparison
    }

    int binarySize;
    int binary[username.length() * 8];
    convertToBinary(username, binary, binarySize);

    int n = imageSize / binarySize;
    encodeImage(image, binary, binarySize, n, imageSize);

    // Write the encoded image to a PPM file in P2 format
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

    cout << "Image encoded successfully. Output file: encoded_image.ppm" << endl;


    // Write the encoded image to a PPM file in P2 format ------------ for comparison (added after so timers are easy to do)
    ofstream outputFile1("plain_image.ppm");
    outputFile1 << "P2" << endl << width << " " << height << endl << "255" << endl;
    for (int i = 0; i < imageSize; i++) {
        outputFile1 << imageNon[i] << " ";
        if ((i + 1) % width == 0) {
            outputFile1 << endl;
        }
    }
    outputFile1.close();
    delete[] imageNon;

    cout << "Image created successfully. Output file: plain_image.ppm" << endl;// ------- for comparison

    return 0;
}