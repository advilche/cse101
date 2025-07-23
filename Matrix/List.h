// -------------------------------------------------------------------
// List.h
// Header file for List ADT
// --------------------------------------------------------------------

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>

// --------------------------------------------------------------------

typedef struct NodeObj* Node;
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);      // Creates and returns a new empty List.

void freeList(List* pL); // Frees all heap memory associated with *pL, and sets *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
void* front(List L); // Returns front element of L. Pre: length()>0
void* back(List L); // Returns back element of L. Pre: length()>0
void* get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
//bool equals(List A, List B); // Returns true iff Lists A and B contain the same sequence of elements, false otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L);	 // Resets L to its original empty state.
void set(List L, void* x); // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void moveFront(List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element, otherwise does nothing.
void movePrev(List L); // Moves cursor one step toward front; if at front, cursor becomes undefined.
void moveNext(List L);  // Moves cursor one step toward back; if at back, cursor becomes undefined.
void prepend(List L, void* x); // Inserts new element before front.
void append(List L, void* x); // Inserts new element after back.
void insertBefore(List L, void* x); // Inserts new element before cursor. Pre: length()>0, index()>=0
void insertAfter(List L, void* x); // Inserts new element after cursor. Pre: length()>0, index()>=0
void deleteFront(List L); // Deletes the front element. Pre: length()>0
void deleteBack(List L); // Deletes the back element. Pre: length()>0
void delete(List L); // Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints a string representation of L.
//List copyList(List L); // Returns a new List representing the same sequence as L. Cursor in new list is undefined.

// Optional function (if you choose to implement it)

// List concatList(List A, List B); // Concatenates A and B into a new List.

#endif // LIST_H_INCLUDE_
