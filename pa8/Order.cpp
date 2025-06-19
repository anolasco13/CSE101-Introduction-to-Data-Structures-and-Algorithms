/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA8
 * Order.cpp
 * Ordering program 
***/


#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    // Ensure correct usage
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    // Open input and output files
    std::ifstream inputFile(argv[1], std::ios::in);
    std::ofstream outputFile(argv[2], std::ios::out);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }

    // Create a Dictionary object
    Dictionary dict;

    // Read lines from the input file
    std::string line;
    long long lineNumber = 1;  // Use long long to handle large numbers of lines

    while (std::getline(inputFile, line)) {
        try {
            dict.setValue(line, lineNumber);  // Insert line as key with line number as value
            lineNumber++;
        } catch (const std::bad_alloc&) {
            std::cerr << "Error: Memory allocation failed while inserting into the dictionary." << std::endl;
            inputFile.close();
            outputFile.close();
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            inputFile.close();
            outputFile.close();
            return 1;
        }
    }

    // Close the input file
    inputFile.close();

    try {
        // Write the dictionary's in-order string representation to the output file
        outputFile << dict.to_string() << std::endl;

        // Write the dictionary's pre-order string representation to the output file
        outputFile << dict.pre_string() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: Failed to write to output file. " << e.what() << std::endl;
        outputFile.close();
        return 1;
    }

    // Close the output file
    outputFile.close();

//    std::cout << "Processing completed successfully!" << std::endl;
    return 0;
}

