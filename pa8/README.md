**CSE 101 Programming Assignment 8**

This assignment involves implementing a `Dictionary` Abstract Data Type (ADT) using a Red-Black Tree (RBT). The implementation includes a variety of components, from the ADT's core logic to test clients and utilities for text processing. Below is a breakdown of the files included in this project and their roles:

1. **Dictionary.h**
   - Provided header file defining the 'Dictionary' ADT
   - Declares access functions, constructors, deconstrcutors, manipulation procedures, etc.

2. **Dictionary.cpp**
   - Implements the 'Dictionary' ADT
   - Utilizes a Red-Black Tree as the underlying data structure.
   - Implements all required access, manipulation, and traversal functions

3. **DictionaryTest.cpp**
   - A custom test client for the `Dictionary` ADT.
   - Tests various operations, including insertions, deletions, searches, and traversals.

4. **Order.cpp**
   - Top-level client program inherited from Programming Assignment 7.

5. **WordFrequency.cpp**
   - A new client program designed for text processing and frequency analysis.
   - Reads a text file, tokenizes words, and calculates word frequencies 

6. **Makefile**
   - Automates the compilation process.
   - Includes targets for building `DictionaryTest`, `Order`, and `WordFrequency` executables.
   - Provides a `clean` target to remove generated files.

7. **README.md**
   - This document :P
