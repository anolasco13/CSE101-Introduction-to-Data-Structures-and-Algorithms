/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA8
 * WordFrequency.cpp
 * Word frequency analysis client
 ***/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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

    // Initialize Dictionary for word frequencies
    Dictionary wordFrequency;

    // String delimiter containing whitespace, punctuation, and special characters
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    string line;
    while (getline(inFile, line)) {
        size_t start = line.find_first_not_of(delim);
        while (start != string::npos) {
            size_t end = line.find_first_of(delim, start);
            string word = line.substr(start, end - start);

            // Convert word to all lowercase
            for (char& c : word) {
                c = tolower(c);
            }

            // If word already exists in Dictionary, increment frequency
            if (wordFrequency.contains(word)) {
                wordFrequency.getValue(word)++;
            } else {
                // If word is new, set frequency to 1
                wordFrequency.setValue(word, 1);
            }

            // Update start to search for next word
            start = line.find_first_not_of(delim, end);
        }
    }

    // Write Dictionary to output file in in-order format (key : value)
    outFile << wordFrequency.to_string() << endl;

    // Close files
    inFile.close();
    outFile.close();

    return EXIT_SUCCESS;
}

