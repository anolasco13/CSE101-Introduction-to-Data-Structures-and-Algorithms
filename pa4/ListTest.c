/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA4
 * ListTest.c
 * Handmade tests for List ADT
***/

#include <stdio.h>
#include "List.h"

int main() {
    // Create a new list
    List list = newList();

    // Test prepend and append
    int a = 10, b = 20, c = 30;
    prepend(list, &a);
    append(list, &b);
    append(list, &c);

    // Test moveFront and moveNext
    moveFront(list);
    printf("Front element: %d\n", *(int*)get(list)); // Expected output: 10

    moveNext(list);
    printf("Next element: %d\n", *(int*)get(list)); // Expected output: 20

    // Test moveBack and movePrev
    moveBack(list);
    printf("Back element: %d\n", *(int*)get(list)); // Expected output: 30

    movePrev(list);
    printf("Previous element: %d\n", *(int*)get(list)); // Expected output: 20

    // Test set
    int newValue = 25;
    set(list, &newValue);
    printf("Updated element: %d\n", *(int*)get(list)); // Expected output: 25

    // Test deleteFront and deleteBack
    deleteFront(list);
    deleteBack(list);

    // Test length
    printf("Length of the list: %d\n", length(list)); // Expected output: 1

    // Free the list
    freeList(&list);

    return 0;
}
