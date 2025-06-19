/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA6
 * BigInteger.cpp
 * BigInteger ADT 
***/

#include "BigInteger.h"
#include "List.h"
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>

const int POWER = 9;  // Each node stores up to 10^9.
const long BASE = static_cast<long>(pow(10, POWER));

// Helper function declarations
void addLists(List& result, const List& A, const List& B);
void subtractLists(List& result, const List& A, const List& B);
void multiplyLists(List& result, const List& A, const List& B);
void scalarMultiply(List& L, long m);
void shiftListLeft(List& L, int p);
int compareLists(const List& A, const List& B);

// Class Constructors & Destructors ----------------------------------------

BigInteger::BigInteger() : signum(0), digits() {}

BigInteger::BigInteger(long x) {
    signum = (x > 0) ? 1 : (x < 0) ? -1 : 0;
    x = std::abs(x);

    while (x != 0) {
        digits.insertAfter(x % BASE);
        x /= BASE;
    }
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    // Determine the sign
    if (s[0] == '-') {
        signum = -1;
        s = s.substr(1);
    } else if (s[0] == '+') {
        signum = 1;
        s = s.substr(1);
    } else {
        signum = 1;
    }

    // Validate input string
    if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos) {
        throw std::invalid_argument("BigInteger: Constructor: invalid input string");
    }

    // Handle zero
    if (s == "0") {
        makeZero();
        return;
    }

    // Parse digits in groups of POWER
    int len = s.length();
    for (int i = len; i > 0; i -= POWER) {
        int start = std::max(0, i - POWER);
        std::string sub = s.substr(start, i - start);
        digits.insertAfter(std::stol(sub));
    }
}

BigInteger::BigInteger(const BigInteger& N) : signum(N.signum), digits(N.digits) {}

// Access functions --------------------------------------------------------

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) return (signum < N.signum) ? -1 : 1;

    if (signum == 0) return 0;

    int cmp = compareLists(digits, N.digits);
    return signum * cmp;
}

// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    if (signum != 0) {
        signum *= -1;
    }
}

// BigInteger Arithmetic operations ----------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger result;

    if (signum == 0) return N;
    if (N.signum == 0) return *this;

    if (signum == N.signum) {
        result.signum = signum;
        addLists(result.digits, digits, N.digits);
    } else {
        int cmp = compareLists(digits, N.digits);
        if (cmp == 0) {
            result.makeZero();
        } else if (cmp > 0) {
            result.signum = signum;
            subtractLists(result.digits, digits, N.digits);
        } else {
            result.signum = N.signum;
            subtractLists(result.digits, N.digits, digits);
        }
    }
    return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger negN = N;
    negN.negate();
    return add(negN);
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;

    if (signum == 0 || N.signum == 0) {
        result.makeZero();
        return result;
    }

    result.signum = signum * N.signum;
    multiplyLists(result.digits, digits, N.digits);

    return result;
}

// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string() {
    if (signum == 0) return "0";

    std::string result = (signum == -1) ? "-" : "";
    digits.moveBack();
    while (digits.position() > 0) {
        std::string chunk = std::to_string(digits.movePrev());
        if (digits.position() != 0) {
            result += std::string(POWER - chunk.length(), '0') + chunk;
        } else {
            result += chunk;
        }
    }
    return result;
}

// Overloaded Operators ----------------------------------------------------

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return (A.signum == B.signum) && (A.digits == B.digits);
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    int cmp = A.compare(B);
    return cmp == -1 || cmp == 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    int cmp = A.compare(B);
    return cmp == 1 || cmp == 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}

// Helper Functions Implementation -----------------------------------------

void addLists(List& result, const List& A, const List& B) {
    result.clear();
    List tempA = A;
    List tempB = B;
    tempA.moveBack();
    tempB.moveBack();

    long carry = 0;
    while (tempA.position() > 0 || tempB.position() > 0 || carry != 0) {
        long a = (tempA.position() > 0) ? tempA.movePrev() : 0;
        long b = (tempB.position() > 0) ? tempB.movePrev() : 0;

        long sum = a + b + carry;
        carry = sum / BASE;
        sum %= BASE;

        result.insertAfter(sum);
    }
}

void subtractLists(List& result, const List& A, const List& B) {
    result.clear();
    List tempA = A;
    List tempB = B;
    tempA.moveBack();
    tempB.moveBack();

    long borrow = 0;
    while (tempA.position() > 0) {
        long a = tempA.movePrev();
        long b = (tempB.position() > 0) ? tempB.movePrev() : 0;

        long diff = a - b - borrow;
        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.insertAfter(diff);
    }
}

void multiplyLists(List& result, const List& A, const List& B) {
    result.clear();
    List tempA = A;
    tempA.moveFront();

    int shift = 0;
    while (tempA.position() < tempA.length()) {
        long a = tempA.moveNext();
        List partialProduct = B;
        scalarMultiply(partialProduct, a);
        shiftListLeft(partialProduct, shift++);
        addLists(result, result, partialProduct);
    }
}

void scalarMultiply(List& L, long m) {
    if (m == 0) {
        L.clear();
        return;
    }

    L.moveBack();
    long carry = 0;

    while (L.position() > 0) {
        long val = L.movePrev() * m + carry;
        carry = val / BASE;
        val %= BASE;
        L.setAfter(val);
    }

    if (carry > 0) {
        L.moveFront();
        L.insertAfter(carry);
    }
}

void shiftListLeft(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; ++i) {
        L.insertAfter(0);
    }
}

int compareLists(const List& A, const List& B) {
    if (A.length() > B.length()) return 1;
    if (A.length() < B.length()) return -1;

    List tempA = A;
    List tempB = B;
    tempA.moveFront();
    tempB.moveFront();

    while (tempA.position() < tempA.length()) {
        long a = tempA.peekNext();
        long b = tempB.peekNext();
        if (a != b) {
            return (a > b) ? 1 : -1;
        }
        tempA.moveNext();
        tempB.moveNext();
    }

    return 0;
}

