**CSE 101 Programming Assignment 3**

In this assignment, we built a Graph module in C that implements the Depth First Search algorithm. The Graph module is used to find the strongly connected components of a digraph in a program called FindComponents.c. The required files for this project are as follows:


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
6. FindComponents.c:
	- The main program that finds the strongly connected components of a graph.
	- Implements the Graph ADT
	- Takes two command line arguments
7. Makefile: 
	- The Makefile creates an executable binary called FindComponents, as well as GraphTest and GraphClient
	- Also includes a clean target that removes any associated executables/.o files 
8. README.md: 
	- This document
