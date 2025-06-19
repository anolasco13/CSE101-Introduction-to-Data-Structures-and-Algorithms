/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * ListTest.c
 * Handmade tests for List ADT
***/

#include <stdio.h>
#include "Matrix.h"

int main() {
    Matrix A = newMatrix(3);
    printf("Matrix A:\n");
    printMatrix(stdout, A);
    printf("\n");

    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 3, 2.0);
    changeEntry(A, 2, 2, 3.0);
    changeEntry(A, 3, 1, 4.0);
    changeEntry(A, 3, 3, 5.0);
    printf("Matrix A after setting entries:\n");
    printMatrix(stdout, A);
    printf("\n");

    Matrix A_copy = copy(A);
    printf("Matrix A_copy:\n");
    printMatrix(stdout, A_copy);
    printf("\n");

    Matrix A_transpose = transpose(A);
    printf("Transpose of matrix A:\n");
    printMatrix(stdout, A_transpose);
    printf("\n");

    Matrix A_scaled = scalarMult(2.0, A);
    printf("Matrix A scaled by 2.0:\n");
    printMatrix(stdout, A_scaled);
    printf("\n");

    Matrix A_sum = sum(A, A_copy);
    printf("Sum of matrices A and A_copy:\n");
    printMatrix(stdout, A_sum);
    printf("\n");

    Matrix A_diff = diff(A, A_copy);
    printf("Difference of matrices A and A_copy:\n");
    printMatrix(stdout, A_diff);
    printf("\n");

    Matrix B = newMatrix(3);
    changeEntry(B, 1, 1, 1.0);
    changeEntry(B, 2, 2, 1.0);
    changeEntry(B, 3, 3, 1.0);
    printf("Matrix B:\n");
    printMatrix(stdout, B);
    printf("\n");

    Matrix AB_product = product(A, B);
    printf("Product of matrices A and B:\n");
    printMatrix(stdout, AB_product);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&A_copy);
    freeMatrix(&A_transpose);
    freeMatrix(&A_scaled);
    freeMatrix(&A_sum);
    freeMatrix(&A_diff);
    freeMatrix(&B);
    freeMatrix(&AB_product);

    return 0;
}

