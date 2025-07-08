#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj{
   int data;
   Node next;
   Node prev;
} NodeObj;

typedef struct ListObj{
   int length;          // number of items in this Queue
   Node front;           // index of front element
   Node back;            // index of back element
   Node cursor;          // cursor Node
   int index;		 // Index value of cursor
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int data) {
        Node N = malloc(sizeof(NodeObj));
        assert( N != NULL);
        N->data = data;
        N->next = NULL;
        N->prev = NULL;
        return N;
}

//free Node

void freeNode(Node* pN){
        if ( (pN != NULL) && (*pN != NULL)){
		free(*pN);
		*pN = NULL;
        }
}

// New List

List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;

}

void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while(length(*pL) > 0){
	      deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

int length(List L){
	if(L == NULL){
		fprintf(stderr, "List error: calling length() on NULL List element\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

int getIndex(List L){
	if(L == NULL){
                fprintf(stderr, "List error: calling index() on NULL List element\n");
        	exit(EXIT_FAILURE);
	}
	return L->index;
}

int front(List L){
	if(length(L) > 0){
		return L->front->data; // look at dis later
	}
	else{
		fprintf(stderr, "List error: calling front() on undefined length (length < 0)\n");
		exit(EXIT_FAILURE);;
	}
}

int back(List L){
	if(length(L) > 0){
                return L->back->data; // look at dis later
        }
        else{
                fprintf(stderr, "List error: calling back() on undefined length (length < 0)\n");
		exit(EXIT_FAILURE);;
        }
}

int get(List L){
	if (L->length <= 0) {
        	printf("List Error: calling get() on an empty List\n");
        	exit(EXIT_FAILURE);
	}
    	if (L->index < 0) {
        	printf("List Error: calling get() on undefined cursor\n");
        	exit(EXIT_FAILURE);
        
        }

	return L->cursor->data; // look at dis later
}

bool equals(List A, List B){
	if (A == NULL || B == NULL) {
        	printf("List Error: calling equals() on NULL List reference\n");
        	exit(EXIT_FAILURE);
	}

    	if (A->length != B->length){
		return false;
	}

    	Node NodeA = A->front;
    	Node NodeB = B->front;
    	while (NodeA != NULL) {
        	if (NodeA->data != NodeB->data){
			return false;
		}
        	NodeA = NodeA->next;
        	NodeB = NodeB->next;
    	}
	return true;

}

// Manipulation procedures ----------------------------------------------------

void clear(List L){
	while (L->length > 0){
		deleteFront(L);
	}
	L->cursor = NULL;
	L->index = -1;
}

void set(List L, int x){
	if(L->cursor != NULL){
		L->cursor->data = x;
	}
	else{
		fprintf(stderr, "List error: calling set() on undefined cursor\n");
        	exit(EXIT_FAILURE);
	}
}

void moveFront(List L){
	if(L->length > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L->length > 0){
                L->cursor = L->back;
                L->index = L->length - 1;
        }
}

void movePrev(List L){
	if (L->cursor != NULL && L->cursor != L->front) {
        	L->cursor = L->cursor->prev;
        	L->index -= 1;
	}
	else{
		L->cursor = NULL;
	        L->index = -1;
	}
}


void moveNext(List L){
	if(L->cursor != NULL && L->cursor != L->back){
		L->cursor = L->cursor->next;
		L->index += 1;
	}
	else{
		L->cursor = NULL;
		L->index = -1;
	}
}

void prepend(List L, int x){
	Node N = newNode(x);
	if(L->length > 0){
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	else if (L->length == 0){
		L->front = N;
		L->back = N;
	}
	L->length += 1;
	
	if(L->index != -1){
		L->index += 1;
	}
}

void append(List L, int x){
	if (L == NULL) {
        	printf("List Error: calling append() on NULL List reference\n");
        	exit(EXIT_FAILURE);
    	}
	Node newNode1 = newNode(x);
	if(L->length == 0){
		L->front = newNode1;
                L->back = newNode1;
	}
	else{
		newNode1->prev = L->back;
                L->back->next = newNode1;
                L->back = newNode1;
        }
	L->length += 1;
}

void insertBefore(List L, int x){
	if(L == NULL){
                fprintf(stderr, "List error: calling insertBefore() on NULL list reference\n");
                exit(EXIT_FAILURE);
        }
	
	if ((L->length <= 0) || (L->index < 0)) {
		fprintf(stderr, "List error: calling insertBefore() on empty list or undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	
	
	if (L->cursor == L->front){
		prepend(L,x);
	}

	else{
		Node n = newNode(x);
		n->next = L->cursor;
		n->prev = L->cursor->prev;
		L->cursor->prev->next = n;
		L->cursor->prev = n;
		L->length += 1;
		L->index += 1;
	}
}

void insertAfter(List L, int x){
        if(L == NULL){
		fprintf(stderr, "List error: calling insertAfter() on NULL list reference\n");
                exit(EXIT_FAILURE);
	}
	
	if (L->length <= 0 || L->index < 0) {
                fprintf(stderr, "List error: calling insertAfter() on empty list or undefined cursor\n");
                exit(EXIT_FAILURE);
        }

	if(L->cursor == L->back){
		append(L, x);
	}
        else{
                Node n = newNode(x);
		n->prev = L->cursor;
		n->next = L->cursor->next;
		L->cursor->next->prev = n;
		L->cursor->next = n;
		L->length += 1;
        }
}


void deleteFront(List L){
	if (L == NULL) {
        	printf("List Error: calling deleteFront() on NULL List reference\n");
        	exit(EXIT_FAILURE);
   	}
    	if (L->length <= 0) {
        	printf("List Error: calling deleteFront() on an empty List\n");
        	exit(EXIT_FAILURE);
    	}
    	
	Node N = L->front;
    	if (L->length > 1) {
        	L->front = L->front->next;
        	L->front->prev = NULL;
    	}

    	else{
        	L->front = L->back = NULL;
    	}

    	if (L->cursor == N) {
        	L->cursor = NULL;
        	L->index = -1;
    	}
    	
	freeNode(&N);
    	L->length -= 1;
    	if (L->index != -1){
		L->index--;
    	}
}


void deleteBack(List L){
        if(L->length <= 0){
                fprintf(stderr, "List error: calling deleteBack() on empty list\n");
        	exit(EXIT_FAILURE);
	}

	Node temp = L->back;
	if(L->length > 1){
		L->back = L->back->prev;
		L->back->next = NULL;
	}

	else{
		L->back = NULL;
		L->front = NULL;
	}

	if(L->cursor == temp){
		L->cursor = NULL;
		L->index = -1;
	}


	freeNode(&temp);
	L->length -= 1;
}

void delete(List L){
	if((length(L) <= 0 || L->cursor->data < 0)){
                fprintf(stderr, "List error: calling delete() on empty list\n");
        	exit(EXIT_FAILURE);
	}
	
	Node N = L->cursor;
    	if (N == L->front) {
        	deleteFront(L);
    	} 
	else if (N == L->back) {
        	deleteBack(L);
    	}
       	else{
        	N->prev->next = N->next;
        	N->next->prev = N->prev;
        	freeNode(&N);
        	L->length -= 1;
    	}
    	L->cursor = NULL;
    	L->index = -1;
}


void printList(FILE* out, List L){
	Node current = L->front;
    	while (current != NULL) {
        	fprintf(out, "%d ", current->data);
        	current = current->next;
    	}
    	fprintf(out, "\n");
}

List copyList(List L){
	List newList1 = newList();
    	Node current = L->front;
    	while (current != NULL) {
        	append(newList1, current->data);
        	current = current->next;
    	}
	return newList1;
}
