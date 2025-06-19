/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA6
 * Arithmetic.cpp
 * Top Level Client 
***/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Helper to parse a number into a vector of digits and track its sign
std::pair<std::vector<int>, int> parseBigInteger(const std::string& number) {
    std::vector<int> result;
    int sign = 1;

    for (char digit : number) {
        if (digit == '-') {
            sign = -1; // Negative number
        } else if (isdigit(digit)) {
            result.push_back(digit - '0');
        }
    }

    // Strip leading zeros
    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin());
    }

    return {result, sign};
}

// Helper to convert a vector of digits back to a string with a sign
std::string vectorToString(const std::vector<int>& number, int sign) {
    std::string result;
    
    // If the number is negative and not zero, prepend the negative sign
    if (sign == -1 && !(number.size() == 1 && number[0] == 0)) {
        result.push_back('-');
    }

    // Skip leading zeros in the vector
    bool leadingZero = true;
    for (int digit : number) {
        if (digit != 0) {
            leadingZero = false;
        }
        if (!leadingZero) {
            result.push_back(digit + '0');
        }
    }

    // Handle case where the number is all zeros
    if (result.empty() || (sign == -1 && result == "-")) {
        return "0";
    }
    return result;
}

// Helper to add two big integers
std::vector<int> addUnsigned(const std::vector<int>& num1, const std::vector<int>& num2) {
    std::vector<int> result;
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] : 0;
        int digit2 = (j >= 0) ? num2[j--] : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back(sum % 10);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Helper to subtract two big integers (assumes num1 >= num2)
std::vector<int> subtractUnsigned(const std::vector<int>& num1, const std::vector<int>& num2) {
    std::vector<int> result;
    int borrow = 0;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0) {
        int digit1 = num1[i--];
        int digit2 = (j >= 0) ? num2[j--] : 0;

        digit1 -= borrow;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(digit1 - digit2);
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back(); // Remove trailing zeros
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Helper to compare two unsigned big integers
int compareUnsigned(const std::vector<int>& num1, const std::vector<int>& num2) {
    if (num1.size() != num2.size()) {
        return (num1.size() > num2.size()) ? 1 : -1;
    }
    for (size_t i = 0; i < num1.size(); ++i) {
        if (num1[i] != num2[i]) {
            return (num1[i] > num2[i]) ? 1 : -1;
        }
    }
    return 0; // Equal
}

// Addition and subtraction with signs
std::pair<std::vector<int>, int> addBigIntegers(const std::vector<int>& num1, int sign1,
                                                const std::vector<int>& num2, int sign2) {
    if (sign1 == sign2) {
        return {addUnsigned(num1, num2), sign1};
    }
    int cmp = compareUnsigned(num1, num2);
    if (cmp >= 0) {
        return {subtractUnsigned(num1, num2), sign1};
    } else {
        return {subtractUnsigned(num2, num1), sign2};
    }
}

std::pair<std::vector<int>, int> subtractBigIntegers(const std::vector<int>& num1, int sign1,
                                                     const std::vector<int>& num2, int sign2) {
    return addBigIntegers(num1, sign1, num2, -sign2);
}

// Helper to multiply two big integers
std::pair<std::vector<int>, int> multiplyBigIntegers(const std::vector<int>& num1, int sign1,
                                                     const std::vector<int>& num2, int sign2) {
    std::vector<int> result(num1.size() + num2.size(), 0);

    for (int i = num1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; --j) {
            int product = num1[i] * num2[j] + result[i + j + 1] + carry;
            carry = product / 10;
            result[i + j + 1] = product % 10;
        }
        result[i] += carry;
    }

    while (result.size() > 1 && result[0] == 0) {
        result.erase(result.begin()); // Remove leading zeros
    }

    int resultSign = (sign1 * sign2);
    return {result, resultSign};
}

// Function to compute power with repeated multiplications
std::pair<std::vector<int>, int> powerBigInteger(const std::vector<int>& base, int baseSign,
                                                 int exponent) {
    std::vector<int> result = {1};
    int resultSign = 1;

    for (int i = 0; i < exponent; ++i) {
        auto [tempResult, tempSign] = multiplyBigIntegers(result, resultSign, base, baseSign);
        result = tempResult;
        resultSign = tempSign;
    }
    return {result, resultSign};
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Arithmetic <input file> <output file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }

    // Read numbers from the file
    std::string A_str, blank, B_str;
    std::getline(input, A_str);
    std::getline(input, blank); // Skip blank line
    std::getline(input, B_str);

    // Parse strings into vectors of digits with signs
    auto [A, signA] = parseBigInteger(A_str);
    auto [B, signB] = parseBigInteger(B_str);

    // Perform operations
    auto [sum, signSum] = addBigIntegers(A, signA, B, signB);                   // A + B
    auto [diff1, signDiff1] = subtractBigIntegers(A, signA, B, signB);          // A - B
    auto [diff2, signDiff2] = subtractBigIntegers(A, signA, A, signA);          // A - A (results in 0)
    auto [threeA, signThreeA] = multiplyBigIntegers(A, signA, {3}, 1);          // 3A
    auto [twoB, signTwoB] = multiplyBigIntegers(B, signB, {2}, 1);              // 2B
    auto [linearCombination, signLinearCombination] = subtractBigIntegers(threeA, signThreeA, twoB, signTwoB); // 3A - 2B
    auto [product, signProduct] = multiplyBigIntegers(A, signA, B, signB);      // A * B
    auto [squareA, signSquareA] = multiplyBigIntegers(A, signA, A, signA);      // A^2
    auto [squareB, signSquareB] = multiplyBigIntegers(B, signB, B, signB);      // B^2

    // Compute 9A^4 and 16B^5
    auto [A4, signA4] = powerBigInteger(A, signA, 4);
    auto [term1, signTerm1] = multiplyBigIntegers(A4, signA4, {9}, 1);
    auto [B5, signB5] = powerBigInteger(B, signB, 5);
    auto [term2, signTerm2] = multiplyBigIntegers(B5, signB5, {16}, 1);

    // Final expression: 9A^4 + 16B^5
    auto [finalExpression, finalSign] = addBigIntegers(term1, signTerm1, term2, signTerm2);

    // Write results to output
    output << vectorToString(A, signA) << "\n\n";
    output << vectorToString(B, signB) << "\n\n";
    output << vectorToString(sum, signSum) << "\n\n";
    output << vectorToString(diff1, signDiff1) << "\n\n";
    output << vectorToString(diff2, signDiff2) << "\n\n";
    output << vectorToString(linearCombination, signLinearCombination) << "\n\n";
    output << vectorToString(product, signProduct) << "\n\n";
    output << vectorToString(squareA, signSquareA) << "\n\n";
    output << vectorToString(squareB, signSquareB) << "\n\n";
    output << vectorToString(finalExpression, finalSign) << "\n\n";

    input.close();
    output.close();

    return 0;
}

