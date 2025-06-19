/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * Matrix.h
 * Header file for Matrix ADT's functions and procedures 
***/


#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdbool.h>

// Exported type
typedef struct MatrixObj* Matrix;

// Constructors-Destructors
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);

// Access functions
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);

// Manipulation Procedures
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE* out, Matrix M);

#endif /* MATRIX_H */
