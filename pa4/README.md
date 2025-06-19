**CSE 101 Programming Assignment 4**

In this assignment, we implemented a Matrix ADT in C. This ADT will perform a series of operations, access functions, and manipulation procedures on matrices. The ADT will be used in a top level client module, Sparse.c, to perform said operations on different matrix inputs. The required files for this project are as follows:

1. List.h: 
	- The header file for the List ADT's functions and procedures
	- Declares access functions, constructors-deconstructors, manipulation procedures, and other operations
	- Implemented from PA1, converted from a List of ints to a List of generic pointers
2. List.c: 
	- The corresponding c file for List.h, containing the functions and procedures declared in the header file
	- Also defines structs
3. Matrix.h:
	- The header file for the Matrix ADT's functions and procedures
4. Matrix.c:
	- The corresponding c file for Matrix.h, containing the functions and procedures declared in the header file.
	- Defines a private inner struct encapsulating the column and value information corresponding to a matrix entry 
5. ListTest.c: 
	- A test client for the List ADT intended to test the functionality of all ADT operations in isolation.
6. MatrixTest.c:
	- A test client for the Matrix ADT intended to test the functionality of all ADT operations in isolation.
7. Sparse.c: 
	- The main program that computes a series of operations on matrices.
	- Implements the List and Matrix ADTs
	- Takes two command line arguments 
8. Makefile: 
	- The Makefile creates an executable binary called Sparse, as well as ListTest and MatrixTest
	- Also includes a clean target that removes any associated executables/.o files 
9. README.md: 
	- This document

NOTE FOR GRADER:
My program fails the valgrind tests, more specifically due to my changeEntry function. In this function, I use malloc to allocate memory for a new entry. However, if I try to deallocate at the end of my function, all other arithmetic operations in my Matrix ADT lose their functionality, since they need this memory to operate. I have also tried freeing in each function that utilizes the changeEntry function. This does not work either, in fact it makes my Sparse program not work at all. I have used resources, attended tutor sessions, and even found some peers with the same issue. Because of this, I hope to get more partial credit rather than completely failing the valgrind tests. Thank you. 
