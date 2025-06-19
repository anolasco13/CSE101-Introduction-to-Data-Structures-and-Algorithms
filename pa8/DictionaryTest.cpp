/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA8
 * DictionaryTest.cpp
 * Dictionary ADT Test Script 
***/

// DictionaryTest.cpp
#include <iostream>
#include "Dictionary.h"

int main() {
    // Create a Dictionary instance
    Dictionary dict;

    // Test 1: Insert key-value pairs
    std::cout << "Inserting key-value pairs..." << std::endl;
    dict.setValue("alpha", 1);
    dict.setValue("beta", 2);
    dict.setValue("gamma", 3);
    dict.setValue("delta", 4);
    std::cout << "Dictionary contents:\n" << dict << std::endl;

    // Test 2: Retrieve values using keys
    std::cout << "\nRetrieving values:" << std::endl;
    if (dict.contains("alpha")) {
        std::cout << "alpha: " << dict.getValue("alpha") << std::endl;
    }
    if (dict.contains("beta")) {
        std::cout << "beta: " << dict.getValue("beta") << std::endl;
    }

    // Test 3: Update an existing key
    std::cout << "\nUpdating value for 'alpha' to 10..." << std::endl;
    dict.setValue("alpha", 10);
    std::cout << "Updated Dictionary:\n" << dict << std::endl;

    // Test 4: Deletion
    std::cout << "\nRemoving 'beta'..." << std::endl;
    dict.remove("beta");
    std::cout << "After removal:\n" << dict << std::endl;

    // Test 5: Iteration
    std::cout << "\nIterating through Dictionary in-order:" << std::endl;
    dict.begin();
    while (dict.hasCurrent()) {
        std::cout << dict.currentKey() << ": " << dict.currentVal() << std::endl;
        dict.next();
    }

    // Test 6: Equals function
    std::cout << "\nTesting equality operator..." << std::endl;
    Dictionary dict2;
    dict2.setValue("alpha", 10);
    dict2.setValue("gamma", 3);
    dict2.setValue("delta", 4);

    if (dict == dict2) {
        std::cout << "Dictionaries are equal." << std::endl;
    } else {
        std::cout << "Dictionaries are not equal." << std::endl;
    }

    // Test 7: Clear
    std::cout << "\nClearing Dictionary..." << std::endl;
    dict.clear();
    std::cout << "Dictionary size after clearing: " << dict.size() << std::endl;

    return 0;
}

