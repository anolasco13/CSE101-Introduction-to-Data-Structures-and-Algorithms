**CSE 101 Programming Assignment 1**

In this assignment, we were instructed to build an Integer List ADT in C, and used it to indirectly alphabetize the lines in a file through a program called Lex. The required files for this project are as follows:

1. List.h:
        - The header file for the List ADT's functions and procedures
        - Declares access functions, constructors-deconstructors, manipulation procedures, and other operations
2. List.c:
        - The corresponding c file for List.h, containing the functions and procedures declared in the header file
        - Also defines structs
3. ListTest.c:
        - A test client for the List ADT intended to test the functionality of all ADT operations
4. Lex.c:
        - The main program that returns a lexicographically ordered output list
        - Implements the List ADT
        - Takes two command line arguments
5. Makefile:
        - The Makefile creates an executable binary called Lex, as well as ListTest and ListClient
        - Also includes a clean target that removes any associated executables/.o files
6. README.md:
        - This document
