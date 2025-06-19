**CSE 101 Programming Assignment 2**

In this assignment, we implemented a Graph ADT in C, as well as our List ADT from Assignment 1, and used them to perform a Breadth First Search algorithm to find the shortest possible paths of a graph. Our main program is called FindPath. The required files for this project are as follows:

1. List.h: 
	- The header file for the List ADT's functions and procedures
	- Declares access functions, constructors-deconstructors, manipulation procedures, and other operations
2. List.c: 
	- The corresponding c file for List.h, containing the functions and procedures declared in the header file
	- Also defines structs
3. Graph.h:
	- The header file for the Graph ADT's functions and procedures
	- Defines a type called Graph that is a pointer to the GraphObj struct in Graph.c
4. Graph.c:
	- The corresponding c file for Graph.h, containing the functions and procedures declared in the header file.
	- Defines a struct called GraphObj 
5. GraphTest.c: 
	- A test client for the Graph ADT intended to test the functionality of all ADT operations in isolation.
4. FindPath.c: 
	- The main program that finds the shortest paths between pairs of vertices.
	- Implements the Graph ADT
	- Takes two command line arguments 
5. Makefile: 
	- The Makefile creates an executable binary called FindPath, as well as GraphTest and GraphClient
	- Also includes a clean target that removes any associated executables/.o files 
6. README.md: 
	- This document
