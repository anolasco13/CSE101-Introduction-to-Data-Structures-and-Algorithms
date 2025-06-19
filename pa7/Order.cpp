/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA7
 * Order.cpp
 * Top level client 
***/

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    // Open input and output files
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open input file " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output file " << argv[2] << endl;
        return EXIT_FAILURE;
    }

    // Initialize Dictionary
    Dictionary dict;

    // Read input file line by line and insert into Dictionary
    string line;
    int lineNumber = 1;
    while (getline(inFile, line)) {
        dict.setValue(line, lineNumber);
        lineNumber++;
    }

    // Write the Dictionary to output file in in-order format (key : value)
    outFile << dict.to_string() << endl;

    // Write the pre-order representation of the Dictionary (keys only)
    outFile << dict.pre_string() << endl;

    // Close files
    inFile.close();
    outFile.close();

    return EXIT_SUCCESS;
}

