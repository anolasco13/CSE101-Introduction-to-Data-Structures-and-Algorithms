/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA1
 * ListTest.c
 * Handmade tests for List ADT
***/

#include <stdio.h>
#include "List.h"

int main() {
    // Create a new list
    List myList = newList();

    // Test insert and moveFront
    for (int i = 1; i <= 5; i++) {
        append(myList, i * 10);
    }

    // TestprintList
    printf("Original List: ");
    printList(stdout, myList);
    printf("\n");

    // Test moveFront, moveNext, and get
    moveFront(myList);
    printf("Current Element: %d\n", get(myList));

    moveNext(myList);
    printf("Next Element: %d\n", get(myList));

    // Test moveBack, movePrev, and get
    moveBack(myList);
    printf("Last Element: %d\n", get(myList));

    movePrev(myList);
    printf("Previous Element: %d\n", get(myList));

    // Test insertBefore and insertAfter
    insertBefore(myList, 999);
    insertAfter(myList, 888);
    
    // test length function 
    int listLength = length(myList);
    printf("List: ");
    printList(stdout, myList);
    printf("\nList Length: %d\n", listLength);

    // Test printList after insertions
    printf("List after insertions: ");
    printList(stdout, myList);
    printf("\n");

    // Test deleteFront and deleteBack
    deleteFront(myList);
    deleteBack(myList);

    // Test printList after deletions
    printf("List after deletions: ");
    printList(stdout, myList);
    printf("\n");

    // Test clear
    clear(myList);

    // Test printList after clear
    printf("List after clear: ");
    printList(stdout, myList);
    printf("\n");

    // free the list
    freeList(&myList);

    return 0;
}
