#pragma once

#include <fstream>

using std::string, std::ifstream, std::ios;

class File {
public:
    static bool checkEmpty(const string& fileName) {
        ifstream file(fileName, ios::binary | ios::ate);
        if (!file.is_open()) {
            throw "Could not open the file: " + fileName;
            return false; // Handle the error as needed
        }
        std::streampos fileSize = file.tellg(); // Get the file size
        file.close();
        return fileSize == 0; // Return true if the file size is zero
    }
};