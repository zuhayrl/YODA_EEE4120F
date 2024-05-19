#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to convert binary representation to a string
string convertFromBinary(int* binary, int binarySize) {
    string output;
    for (int i = 0; i < binarySize; i += 8) {
        int value = 0;
        for (int j = 0; j < 8; ++j) {
            //printf("Bin %d: %d \n", i+j, binary[i+j]);
            value = (value << 1) | binary[i + j];
        }
        output += static_cast<char>(value);
    }
    return output;
}

// Function to decode the binary data from the image using LSB encoding
void decodeImage(int* image, int imageSize, int n, int binarySize, int* binary) {
    int binaryIndex = 0;
    for (int i = 0; i < imageSize; i += n) {
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
    int* image = new int[imageSize];

    //read image data from file into array
    for (int i = 0; i < imageSize; i++) {
        inputFile >> image[i];
    }
    inputFile.close();

    int binarySize = username.length() * 8;
    int* binary = new int[binarySize];

    int n = imageSize / binarySize;
    //decoding
    decodeImage(image, imageSize, n, binarySize, binary);

    string decodedUsername = convertFromBinary(binary, binarySize);

    cout << "Decoded username from image: " << decodedUsername << endl;

    if (username == decodedUsername) {
        cout << "Username matches the encoded image." << endl;
    } else {
        cout << "Username does not match the encoded image." << endl;
    }

    delete[] image;
    delete[] binary;

    return 0;
}
