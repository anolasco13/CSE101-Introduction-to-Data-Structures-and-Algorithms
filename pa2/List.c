/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA2
 * List.c
 * Corresponding c file for List.h
***/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"


// Private NodeObj type
typedef struct NodeObj {
	int data;
        struct NodeObj* prev;
        struct NodeObj* next;
} NodeObj;

// Private Node type
typedef NodeObj* Node;

// Private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new empty List.
List newList(void) {
	List L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
	return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
	return (L->cursor == NULL) ? -1 : L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
    if (length(L) > 0) {	
        return L->front->data;
    } else {
        fprintf(stderr, "Error: Calling front() on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Returns back element of L. Pre: length()>0
int back(List L) {
    if (length(L) > 0) {
        return L->back->data;
    } else {
        fprintf(stderr, "Error: Calling back() on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if (length(L) > 0 && index(L) >= 0) {
        return L->cursor->data;
    } else {
        fprintf(stderr, "Error: Calling get() with undefined cursor or on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Returns true iff Lists A and B are in the same state, and returns false otherwise.
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Error: Comparing with NULL lists\n");
        exit(EXIT_FAILURE);
    }

    if (length(A) != length(B)) {
        return false;
    }

    Node N = A->front;
    Node M = B->front;

    while (N != NULL && M != NULL) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }

    return true;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
    while (length(L) > 0) {
        deleteFront(L);
    }
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
    if (length(L) > 0 && index(L) >= 0) {
        L->cursor->data = x;
    } else {
        fprintf(stderr, "Error: Calling set() with undefined cursor or on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (length(L) > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (length(L) > 0) {
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

// If cursor is defined and not at the front, move cursor one step toward the front of L;
// if cursor is defined and at the front, cursor becomes undefined;
// if cursor is undefined do nothing.
void movePrev(List L) {
    if (L->cursor != NULL) {
        if (L->cursor != L->front) {
            L->cursor = L->cursor->prev;
            L->index--;
        } else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

// If cursor is defined and not at the back, move cursor one step toward the back of L;
// if cursor is defined and at the back, cursor becomes undefined;
// if cursor is undefined do nothing.
void moveNext(List L) {
    if (L->cursor != NULL) {
        if (L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->index++;
        } else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before the front element.
void prepend(List L, int x) {
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->prev = NULL;
    N->next = L->front;

    if (length(L) == 0) {
        L->back = N;
    } else {
        L->front->prev = N;
    }

    L->front = N;
    L->length++;
    // If cursor is defined, increment index
    if (L->cursor != NULL) {
        L->index++;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place after the back element.
void append(List L, int x) {
    Node N = malloc(sizeof(NodeObj));
    N->data = x;
    N->prev = L->back;
    N->next = NULL;

    if (length(L) == 0) {
        L->front = N;
    } else {
        L->back->next = N;
    }

    L->back = N;
    L->length++;
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (length(L) > 0 && index(L) >= 0) {
        Node N = malloc(sizeof(NodeObj));
        N->data = x;
        N->prev = L->cursor->prev;
        N->next = L->cursor;

        if (L->cursor->prev != NULL) {
            L->cursor->prev->next = N;
        } else {
            L->front = N;
        }

        L->cursor->prev = N;
        L->length++;
        L->index++;
    } else if (index(L) == 0) {
	    // if cursor is at front, prepend instead of insertBefore
	    prepend(L, x);
    } else {
        fprintf(stderr, "Error: Calling insertBefore() with undefined cursor or on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (length(L) > 0 && index(L) >= 0) {
        Node N = malloc(sizeof(NodeObj));
        N->data = x;
        N->prev = L->cursor;
        N->next = L->cursor->next;

        if (L->cursor->next != NULL) {
            L->cursor->next->prev = N;
        } else {
            L->back = N;
        }

        L->cursor->next = N;
        L->length++;
        if (L->cursor == L->back) {
            L->back = N;
        }
    } else if (index(L) == length(L) - 1) {
        // If cursor is at the back, append instead of insertAfter
	append(L, x);
    } else {
	fprintf(stderr, "Error: Calling insertAfter() with undefined cursor or on an empty list\n");
	exit(EXIT_FAILURE);
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (length(L) > 0) {
        Node N = L->front;
        if (length(L) == 1) {
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        } else {
            L->front = L->front->next;
            L->front->prev = NULL;
            // If cursor is defined, decrement index
            if (L->cursor != NULL) {
                L->index--;
            }
        }
        free(N);
        L->length--;
    } else {
        fprintf(stderr, "Error: Calling deleteFront() on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (length(L) > 0) {
        Node N = L->back;
        if (length(L) == 1) {
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        } else {
            L->back = L->back->prev;
            L->back->next = NULL;
            // If cursor is defined and at the back, cursor becomes undefined
             if (L->cursor == N) {
                L->cursor = NULL;
                L->index = -1;
            }
        }
        free(N);
        L->length--;
    } else {
        fprintf(stderr, "Error: Calling deleteBack() on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
    if (length(L) > 0 && index(L) >= 0) {
        Node N = L->cursor;

        if (L->cursor->prev != NULL) {
            L->cursor->prev->next = L->cursor->next;
        } else {
            L->front = L->cursor->next;
        }

        if (L->cursor->next != NULL) {
            L->cursor->next->prev = L->cursor->prev;
        } else {
            L->back = L->cursor->prev;
        }

        L->cursor = NULL;
        L->index = -1;
        free(N);
        L->length--;
    } else {
        fprintf(stderr, "Error: Calling delete() with undefined cursor or on an empty list\n");
        exit(EXIT_FAILURE);
    }
}

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space-separated sequence of integers, with front on the left.
void printList(FILE* out, List L) {
    Node N = L->front;
    while (N != NULL) {
        fprintf(out, "%d ", N->data);
        N = N->next;
    }
}

// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L) {
    List copy = newList();
    Node N = L->front;

    while (N != NULL) {
        append(copy, N->data);
        N = N->next;
    }

    return copy;
}
