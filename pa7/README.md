**CSE 101 Programming Assignment 7**

In this assignment, we implemented a Dictionary ADT in C++ based on a Binary Search Tree (BST). The Dictionary supports various operations, such as insertion, deletion, searching, and iterating through keys in sorted order. Additionally, a client program demonstrates its usage for managing key-value pairs. The following files are required for this project:

1. **Dictionary.h**:
   - The header file for the Dictionary ADT's functions and procedures.
   - Declares access functions, manipulation procedures, and other operations.
   - Includes typedefs for keyType (`std::string`) and valType (`int`).

2. **Dictionary.cpp**:
   - The implementation file for the Dictionary ADT, containing the methods declared in the header file.
   - Implements operations like `setValue`, `getValue`, `remove`, and built-in iterator support using a BST.

3. **DictionaryTest.cpp**:
   - A test client for the Dictionary ADT designed to test all the operations and verify the functionality of the BST-based implementation.
   - Includes tests for insertion, deletion, retrieval, iteration, and equality checks.

4. **Order.cpp**:
   - The main client program for this project.
   - Reads lines from an input file and inserts them as keys into the Dictionary.
   - Outputs two string representations of the Dictionary: one in sorted order and one in pre-order traversal.

5. **Makefile**:
   - Automates the compilation of the project.
   - Includes targets for building `DictionaryTest` and `Order` executables.
   - Also includes a `clean` target to remove compiled binaries and object files.

6. **README.md**:
   - This document.

**Notes for Grader**:

I would like to state that my Order.cpp is timing out for the very last test on the autoscript. Upon testing my script with the according input file from cse-101-public-tests, I find that my scipt does produce the correct output. I am hoping for some partial credit on those few points, as you can see my script passes all tests beforehand.

Please take a look at the link below for a screenshot of the commands I used to prove my code passes the last test:

https://drive.google.com/file/d/12PBvLpzGnLZJr5EDQJLmo9gqL9GYj9UW/view?usp=sharing  
