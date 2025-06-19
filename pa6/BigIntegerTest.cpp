/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA6
 * BigIntegerTest.cpp
 * Test Client for BigInteger
***/


#include "BigInteger.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    cout << "Starting BigInteger Tests..." << endl;

    // Testing Constructors
    BigInteger A;
    assert(A.sign() == 0);  // A should be 0 initially
    cout << "Constructor test passed: A == 0" << endl;

    BigInteger B(123456789);
    assert(B.sign() == 1);
    cout << "Constructor test passed: B == 123456789" << endl;

    BigInteger C("-987654321");
    assert(C.sign() == -1);
    cout << "Constructor test passed: C == -987654321" << endl;

    BigInteger D = B;
    assert(D == B);
    cout << "Copy constructor test passed: D == B" << endl;

    // Testing Addition
    BigInteger E = B + C;
    assert(E.sign() == 1);
    cout << "Addition test passed: B + C == " << E << endl;

    // Testing Subtraction
    BigInteger F = B - C;
    assert(F.sign() == 1);
    cout << "Subtraction test passed: B - C == " << F << endl;

    BigInteger G = C - B;
    assert(G.sign() == -1);
    cout << "Subtraction test passed: C - B == " << G << endl;

    // Testing Multiplication
    BigInteger H = B * C;
    assert(H.sign() == -1);
    cout << "Multiplication test passed: B * C == " << H << endl;

    // Testing MakeZero
    A.makeZero();
    assert(A.sign() == 0);
    cout << "makeZero test passed: A == " << A << endl;

    // Testing Negate
    B.negate();
    assert(B.sign() == -1);
    cout << "Negation test passed: -B == " << B << endl;

    B.negate();  // Change back to positive
    assert(B.sign() == 1);
    cout << "Double negation test passed: B == " << B << endl;

    // Testing Comparisons
    assert(B > C);
    assert(C < B);
    assert(B == B);
    assert(B >= B);
    assert(C <= C);
    cout << "Comparison operators test passed" << endl;

    // Testing Addition Assignment
    B += C;
    cout << "Addition assignment test: B += C == " << B << endl;

    // Testing Subtraction Assignment
    B -= C;
    cout << "Subtraction assignment test: B -= C == " << B << endl;

    // Testing Multiplication Assignment
    B *= C;
    cout << "Multiplication assignment test: B *= C == " << B << endl;

    // Check large numbers
    BigInteger big1("123456789012345678901234567890");
    BigInteger big2("987654321098765432109876543210");
    BigInteger big_sum = big1 + big2;
    BigInteger big_product = big1 * big2;

    cout << "Large number addition: " << big1 << " + " << big2 << " = " << big_sum << endl;
    cout << "Large number multiplication: " << big1 << " * " << big2 << " = " << big_product << endl;

    cout << "All tests passed!" << endl;

    return 0;
}

