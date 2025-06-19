/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * List.h
 * Header file for List ADT's functions and procedures 
***/


#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

// Exported type
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void set(List L, void* x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x);
void append(List L, void* x);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);


#endif /* LIST_H */
