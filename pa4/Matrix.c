/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * Matrix.c
 * Corresponding c file for Matrix ADT's functions and procedures 
***/

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>


// Entry object representing a matrix entry (column, value)
typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef EntryObj* Entry;

// Matrix object
typedef struct MatrixObj {
    int size;
    int nnz;
    List* rows;
} MatrixObj;

// Helper function prototypes
double vectorDot(List P, List Q);
void deleteEntry(List list, Entry entry);

// Constructors-Destructors
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;
    M->rows = malloc(n * sizeof(List));
    for (int i = 0; i < n; i++) {
        M->rows[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Matrix M = *pM;
        for (int i = 0; i < M->size; i++) {
            freeList(&(M->rows[i]));
        }
        free(M->rows);
        free(*pM);
        *pM = NULL;
    }
}

// Access functions
int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    return M->nnz;
}

#define EPSILON 1e-9  // Define a small tolerance for floating-point comparison

double absolute(double x) {
    return (x < 0) ? -x : x;
}

int equals(Matrix A, Matrix B) {
    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;  // Matrices have different sizes or different number of non-zero entries
    }

    for (int i = 0; i < size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry entryA = (Entry)get(rowA);
            Entry entryB = (Entry)get(rowB);

            if (entryA->column != entryB->column || absolute(entryA->value - entryB->value) > EPSILON) {
                return 0;  // Entries at the same position are not equal
            }

            moveNext(rowA);
            moveNext(rowB);
        }

        // If one row has more entries than the other, they are not equal
        if (index(rowA) >= 0 || index(rowB) >= 0) {
            return 0;
        }
    }

    return 1;  // Matrices are equal
}



// Manipulation procedures
void makeZero(Matrix M) {
    for (int i = 0; i < size(M); i++) {
        clear(M->rows[i]);
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        exit(EXIT_FAILURE);
    }
    
    List row = M->rows[i - 1];
    Entry currEntry = NULL;
    for (moveFront(row); index(row) >= 0; moveNext(row)) {
        currEntry = (Entry)get(row);
        if (currEntry->column == j) break;
	currEntry = NULL;
    }
    
    if (absolute(x) >= EPSILON) {  // Only add if x is truly non-zero
        if (currEntry == NULL) {
            Entry newEntry = malloc(sizeof(EntryObj));
            
            newEntry->column = j;
            newEntry->value = x;

	    // insert newEntry in sorted order
	    if (length(row) == 0) {
                prepend(row, newEntry);
            } else {
                for (moveFront(row); index(row) >= 0; moveNext(row)) {
                    Entry temp = (Entry)get(row);
                    if (temp->column > j) {
                        insertBefore(row, newEntry);
                        break;
                    } else if (index(row) == length(row) - 1) {
                        append(row, newEntry);
                        break;
                    }
                }
            }
            M->nnz++;  // Increment NNZ for the new entry
        } else {
            // Update existing non-zero entry's value
	    if (absolute(currEntry->value) < EPSILON) {  // Current value is zero, so increment NNZ
                M->nnz++;
            }
            currEntry->value = x;  // Update value
        }

    // Case 2: Removing an entry if x is effectively zero
    } else {
        if (currEntry != NULL) {  // Entry exists and is to be removed
            deleteEntry(row, currEntry);
            free(currEntry);
            M->nnz--;  // Decrement NNZ for removed entry
        }
    }
}

void deleteEntry(List list, Entry entry) {
    if (list == NULL || entry == NULL) {
        return;
    }
    for (moveFront(list); index(list) >= 0; moveNext(list)) {
        Entry temp = (Entry)get(list);
        if (temp == entry) {
            delete(list);
            break;
        }
    }
}

// Matrix Arithmetic operations
Matrix copy(Matrix A) {
    Matrix B = newMatrix(size(A));
    for (int i = 0; i < size(A); i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry entry = (Entry)get(row);
            changeEntry(B, i + 1, entry->column, entry->value);
            moveNext(row);
        }
    }
    return B;
}

Matrix transpose(Matrix A) {
    Matrix T = newMatrix(size(A));
    for (int i = 0; i < size(A); i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry entry = (Entry)get(row);
            changeEntry(T, entry->column, i + 1, entry->value);
            moveNext(row);
        }
    }
    return T;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix B = newMatrix(size(A));
    for (int i = 0; i < size(A); i++) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry entry = (Entry)get(row);
            changeEntry(B, i + 1, entry->column, x * entry->value);
            moveNext(row);
        }
    }
    return B;
}

Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices must be of the same size\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(size(A));
    for (int i = 0; i < size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 || index(rowB) >= 0) {
            Entry entryA = (index(rowA) >= 0) ? (Entry)get(rowA) : NULL;
            Entry entryB = (index(rowB) >= 0) ? (Entry)get(rowB) : NULL;

	    int columnA = (entryA != NULL) ? entryA->column : size(A) + 1;
            int columnB = (entryB != NULL) ? entryB->column : size(B) + 1;  
      
            if (columnA == columnB) {
                double sumValue = entryA->value + entryB->value; 
                if (absolute(sumValue) >= EPSILON) {
                    changeEntry(C, i + 1, columnA, sumValue);
//		    C->nnz++;
                }
                moveNext(rowA);
                moveNext(rowB);
            } else if (columnA < columnB) {
		changeEntry(C, i + 1, columnA, entryA->value);               
  //              C->nnz++;
		moveNext(rowA);
            } else {
   		changeEntry(C, i + 1, columnB, entryB->value); 
    //            C->nnz++;
		moveNext(rowB);
            }
        }
    }
    return C;
}





Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices must be of the same size\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(size(A));
    for (int i = 0; i < size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 || index(rowB) >= 0) {
            int columnA = (index(rowA) >= 0) ? ((Entry)get(rowA))->column : size(A) + 1;
            int columnB = (index(rowB) >= 0) ? ((Entry)get(rowB))->column : size(B) + 1;
            if (columnA == columnB) {
                double diff = ((Entry)get(rowA))->value - ((Entry)get(rowB))->value;
                changeEntry(C, i + 1, columnA, diff);
                moveNext(rowA);
                moveNext(rowB);
            } else if (columnA < columnB) {
                changeEntry(C, i + 1, columnA, ((Entry)get(rowA))->value);
                moveNext(rowA);
            } else {
                changeEntry(C, i + 1, columnB, -((Entry)get(rowB))->value);
                moveNext(rowB);
            }
        }
    }
    //freeMatrix(&C);
    return C;
}

Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "Error: Matrices must be of the same size\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(size(A));
    Matrix BT = transpose(B);
    
    for (int i = 0; i < size(A); i++) {
        List rowA = A->rows[i];
        for (int j = 0; j < size(A); j++) {
            List rowB = BT->rows[j];
            double dotProduct = vectorDot(rowA, rowB);
            if (dotProduct != 0) {
                changeEntry(C, i + 1, j + 1, dotProduct);
            }
        }
    }

    freeMatrix(&BT);
    return C;
}
   
double vectorDot(List P, List Q) {
    double dotProduct = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        int columnP = ((Entry)get(P))->column;
        int columnQ = ((Entry)get(Q))->column;
        if (columnP == columnQ) {
            dotProduct += ((Entry)get(P))->value * ((Entry)get(Q))->value;
            moveNext(P);
            moveNext(Q);
        } else if (columnP < columnQ) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }
    return dotProduct;
}

// Other Operations
void printMatrix(FILE* out, Matrix M) {
    for (int i = 0; i < size(M); i++) {
        List row = M->rows[i];
        if (length(row) > 0) {
            fprintf(out, "%d: ", i + 1);
            moveFront(row);
            while (index(row) >= 0) {
                Entry entry = (Entry)get(row);
                fprintf(out, "(%d, %.1f) ", entry->column, entry->value);
                moveNext(row);
            }
            fprintf(out, "\n");
        }
    }
}



