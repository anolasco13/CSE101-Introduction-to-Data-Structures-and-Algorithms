**CSE 101 Programming Assignment 6**

In this assignment, we created a BigInteger ADT in C++ that supports arithmetic operations on large signed integers. The implementation leverages a List ADT to represent the digits of the BigInteger. The following files are required for this project:

1. List.h: 
	- The header file for the List ADT's functions and procedures
	- Declares access functions, constructors-deconstructors, manipulation procedures, and other operations
2. List.cpp: 
	- The corresponding c++ file for List.h, containing the functions and procedures declared in the header file
	- Uses 2 Node pointers
	- Supports cursor-based navigation, insertion, deletion, and search
3. ListTest.cpp: 
	- A test client for the List ADT intended to test the functionality of all ADT operations
4. BigInteger.h:
	- Header file for BigInteger ADT
	- Declares a signed integer type  
5. BigInteger.cpp:
	- Implementation file for the BigInteger ADT
	- Defines the arithmetic operations and handles edge cases
6. BigIntegerTest.cpp:
	- Test suite for the BigInteger ADT to verify the correctness of arithmetic operations, string conversion, etc.
7. Arithmetic.cpp:
	- Top-level client program for the project
	- Reads two large integers from an input file and performs various arithmetic operations  
8. Makefile: 
	- Automates compilation of the project 
	- Also includes a clean target that removes any associated executables/.o files 
9. README.md: 
	- This document

  
