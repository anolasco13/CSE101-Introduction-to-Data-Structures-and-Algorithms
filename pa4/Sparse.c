/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * Sparse.c
 * Top level client module that performs a series of arithmetic operations on matrices
 ***/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        fprintf(stderr, "Error: Could not open output file %s\n", argv[2]);
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    int n, a, b;
    fscanf(input_file, "%d %d %d", &n, &a, &b);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read and populate matrix A
    for (int i = 0; i < a; i++) {
        int row, col;
        double value;
        fscanf(input_file, "%d %d %lf", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Read and populate matrix B
    for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(input_file, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    fprintf(output_file, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output_file, A);
    fprintf(output_file, "\n");

    fprintf(output_file, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(output_file, B);
    fprintf(output_file, "\n");

    fprintf(output_file, "(1.5)*A =\n");
    Matrix scaled_A = scalarMult(1.5, A);
    printMatrix(output_file, scaled_A);
    fprintf(output_file, "\n");

    fprintf(output_file, "A+B =\n");
    Matrix sum_A_B = sum(A, B);
    printMatrix(output_file, sum_A_B);
    fprintf(output_file, "\n");
    
    // create a local copy of matrix A
    Matrix copyA = copy(A);
    fprintf(output_file, "A+A =\n");
    Matrix sum_A_A = sum(A, copyA);
    printMatrix(output_file, sum_A_A);
    fprintf(output_file, "\n");

    fprintf(output_file, "B-A =\n");
    Matrix diff_B_A = diff(B, A);
    printMatrix(output_file, diff_B_A);
    fprintf(output_file, "\n");

    fprintf(output_file, "A-A =\n");
    Matrix diff_A_A = diff(A, A);
    printMatrix(output_file, diff_A_A);
    fprintf(output_file, "\n");

    fprintf(output_file, "Transpose(A) =\n");
    Matrix transpose_A = transpose(A);
    printMatrix(output_file, transpose_A);
    fprintf(output_file, "\n");

    fprintf(output_file, "A*B =\n");
    Matrix product_A_B = product(A, B);
    printMatrix(output_file, product_A_B);
    fprintf(output_file, "\n");

    fprintf(output_file, "B*B =\n");
    Matrix product_B_B = product(B, B);
    printMatrix(output_file, product_B_B);
    fprintf(output_file, "\n");
 
    fclose(input_file);
    fclose(output_file);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scaled_A);
    freeMatrix(&sum_A_B);
    freeMatrix(&copyA);    
    freeMatrix(&sum_A_A);
    freeMatrix(&diff_B_A);
    freeMatrix(&diff_A_A);
    freeMatrix(&transpose_A);
    freeMatrix(&product_A_B);
    freeMatrix(&product_B_B);

    return 0;
}


