#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    // Create a new list
    List L = newList();
    printf("Created a new empty list.\n");

    // Test: Append elements
    append(L, (void*) 1);
    append(L, (void*) 2);
    append(L, (void*) 3);
    printf("List after appending 1, 2, 3: ");
    printList(stdout, L);
    
    // Test: Move cursor to front and back
    moveFront(L);
    printf("Cursor at front: %d\n", (int) get(L));  // Expect: 1
    moveBack(L);
    printf("Cursor at back: %d\n", (int) get(L));  // Expect: 3

    // Test: Move cursor next and previous
    movePrev(L);
    printf("Cursor moved previous: %d\n", (int) get(L));  // Expect: 2
    moveNext(L);
    printf("Cursor moved next: %d\n", (int) get(L));  // Expect: 3

    // Test: Delete front element
    deleteFront(L);
    printf("List after deleting front element: ");
    printList(stdout, L);  // Expect: 2, 3

    // Test: Delete back element
    deleteBack(L);
    printf("List after deleting back element: ");
    printList(stdout, L);  // Expect: 2

    // Test: Prepend an element
    prepend(L, (void*) 4);
    printf("List after prepending 4: ");
    printList(stdout, L);  // Expect: 4, 2

    // Test: Insert before cursor
    moveFront(L);
    insertBefore(L, (void*) 5);
    printf("List after inserting 5 before cursor: ");
    printList(stdout, L);  // Expect: 5, 4, 2

    // Test: Insert after cursor
    moveNext(L);
    insertAfter(L, (void*) 6);
    printf("List after inserting 6 after cursor: ");
    printList(stdout, L);  // Expect: 5, 4, 6, 2

    // Test: Delete cursor element
    movePrev(L);  // Move cursor to 4
    delete(L);
    printf("List after deleting cursor element: ");
    printList(stdout, L);  // Expect: 5, 6, 2

    // Test: Clear the list
    clear(L);
    printf("List after clearing: ");
    printList(stdout, L);  // Expect: (empty)

    // Free the list
    freeList(&L);
    printf("List after freeing memory.\n");



    return 0;
}