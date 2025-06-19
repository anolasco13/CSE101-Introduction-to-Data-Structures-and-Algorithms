/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA7
 * DictionaryTest.cpp
 * Test client for Dictionary ADT
 */

#include <iostream>
#include "Dictionary.h"

int main() {
    // Create a new Dictionary
    Dictionary dict;

    // Test setValue
    std::cout << "Testing setValue():" << std::endl;
    dict.setValue("apple", 1);
    dict.setValue("banana", 2);
    dict.setValue("cherry", 3);

    // Print the Dictionary
    std::cout << "Current Dictionary (in-order):" << std::endl;
    std::cout << dict.to_string() << std::endl;

    // Test getValue
    std::cout << "Testing getValue():" << std::endl;
    try {
        std::cout << "Value for 'apple': " << dict.getValue("apple") << std::endl;
        std::cout << "Value for 'banana': " << dict.getValue("banana") << std::endl;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // Test contains
    std::cout << "Testing contains():" << std::endl;
    std::cout << "Contains 'cherry': " << dict.contains("cherry") << std::endl;
    std::cout << "Contains 'date': " << dict.contains("date") << std::endl;

    // Test remove
    std::cout << "Testing remove():" << std::endl;
    dict.remove("banana");
    std::cout << "After removing 'banana':" << std::endl;
    std::cout << dict.to_string() << std::endl;

    // Test iterator functions: begin(), end(), next(), prev()
    std::cout << "Testing iterator functions:" << std::endl;
    dict.begin();
    std::cout << "Begin: " << dict.currentKey() << " : " << dict.currentVal() << std::endl;

    dict.next();
    if (dict.hasCurrent()) {
        std::cout << "Next: " << dict.currentKey() << " : " << dict.currentVal() << std::endl;
    }

    dict.end();
    std::cout << "End: " << dict.currentKey() << " : " << dict.currentVal() << std::endl;

    dict.prev();
    if (dict.hasCurrent()) {
        std::cout << "Prev: " << dict.currentKey() << " : " << dict.currentVal() << std::endl;
    }

    // Test clear
    std::cout << "Testing clear():" << std::endl;
    dict.clear();
    std::cout << "After clear, Dictionary size: " << dict.size() << std::endl;

    // Final test for equality operator
    Dictionary dict2;
    dict2.setValue("apple", 1);
    dict2.setValue("cherry", 3);

    std::cout << "Testing equality operator:" << std::endl;
    std::cout << "Are dictionaries equal? " << (dict == dict2) << std::endl;

    return 0;
}

