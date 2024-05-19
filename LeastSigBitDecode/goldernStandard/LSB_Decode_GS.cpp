#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

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

    //Put data from file into array
    for (int i = 0; i < imageSize; i++) {
        inputFile >> image[i];
    }
    inputFile.close();

    int binarySize = username.length() * 8;
    vector<int> binary(binarySize);
    
    int n = imageSize / binarySize;
    decodeImage(image, n, binarySize, binary);

    string decodedUsername = convertFromBinary(binary);

    cout << "Decoded username from image: " << decodedUsername << endl;

    if (username == decodedUsername) {
        cout << "Username matches the encoded image." << endl;
    } else {
        cout << "Username does not match the encoded image." << endl;
    }

    return 0;
}
