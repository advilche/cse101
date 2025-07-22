#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "List.h"
#include "Matrix.h"

typedef struct EntryObj* Entry;
typedef struct MatrixObj* Matrix;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    int size;
    int NNZ;
    List* rows;  
} MatrixObj;

Entry newEntry(int col, double value) {
    	Entry newEntry = malloc(sizeof(EntryObj));
    	newEntry->column = col;
    	newEntry->value = value;
    	return newEntry;
}

void freeEntry(Entry* pE) {
    	if (pE != NULL && *pE != NULL) {
        	free(*pE);
        	*pE = NULL;
    	}
}

double vectorDot(List P, List Q) {
    if (P == NULL || Q == NULL) {
        return 0.0;  // Return 0 ilist is NULL
    }

    moveFront(P);
    moveFront(Q);
    double total = 0.0;

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry entryP = (Entry)get(P);
        Entry entryQ = (Entry)get(Q);

        // Ensure entryQ are valid pointers before accessi their fields
        if (entryP == NULL || entryQ == NULL) {
            return 0.0;  // Avoi deointers
        }

        // Check if colns match
        if (entryP->column == entryQ->column) {
            total += entryP->value * entryQ->value;
            moveNext(P);
            moveNext(Q);
        }
        else if (entryP->column < entryQ->column) {
            moveNext(P);  // Skip entryP
        }
        else {
            moveNext(Q); 
        }
    }

    return total;
}

Matrix newMatrix(int n){
	Matrix newMatrix = malloc(sizeof(MatrixObj));
	
	newMatrix->size = n;
	newMatrix->NNZ = 0;
	newMatrix->rows = calloc(n + 1, sizeof(List));

	for (int i = 1; i <= n; i++) {
        	newMatrix->rows[i] = newList();
    	}

	return newMatrix;	
}

void freeMatrix(Matrix* pM){
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= (*pM)->size; i++) {
            		List row = (*pM)->rows[i];
            		moveFront(row);
            		while (index(row) >= 0) {
                		Entry tempEntry = (Entry)get(row);
                		freeEntry(&tempEntry);
                		moveNext(row);
            		}
            	freeList(&(*pM)->rows[i]);
        	}
        	free((*pM)->rows);
        	free(*pM);
        	*pM = NULL;
    	}
}

// Access functions

int size(Matrix M){
	return M->size;
}

int NNZ(Matrix M){
	return M->NNZ;
}


int equals(Matrix A, Matrix B){
	if (A->NNZ != B->NNZ || A->size != B->size) {
		return 0;
	}

	for (int i = 1; i <= A->size; i++) {
		List rowsofA = A->rows[i];
		List rowsofB = B->rows[i];

		moveFront(rowsofA);
		moveFront(rowsofB);

		// Skip rows if both are empty
		if (length(rowsofA) == 0 && length(rowsofB) == 0) {
			continue;
		} else {
			break;
		}

		// Check if row lengths differ
		if (length(rowsofA) != length(rowsofB)) {
			return 0;
		}

		// Compare each entry in the current row
		while (index(rowsofA) >= 0 && index(rowsofB) >= 0) {
			Entry entryA = (Entry)get(rowsofA);
			Entry entryB = (Entry)get(rowsofB);

			// Check for mismatch in column or value
			if (entryA->column != entryB->column || entryA->value != entryB->value) {
				return 0;
			}

			moveNext(rowsofA);
			moveNext(rowsofB);
		}

		// Ensure both lists reached the end simultaneously
		if (index(rowsofA) >= 0 || index(rowsofB) >= 0) {
			return 0;
		}
	}

	return 1;
}


void makeZero(Matrix M){
	for (int i = 1; i <= M->size; i++) {
        	List rowM = M->rows[i];
        	moveFront(rowM);
        	while (index(rowM) >= 0) {
            		Entry tempEntry = (Entry)get(rowM);
            		freeEntry(&tempEntry);
            		moveNext(rowM);
        	}
        	clear(rowM);
    	}
    	M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
    List rowM = M->rows[i]; 
    moveFront(rowM);

    while (index(rowM) >= 0) {
        Entry tempEntry = (Entry)get(rowM);

        if (tempEntry->column == j) {
            if (x == 0) {
                // Remove existing entry if x is 0
                delete(rowM);
                freeEntry(&tempEntry);
                M->NNZ--;
            } else {
                // Update the value without changing NNZ
                tempEntry->value = x;
            }
            return;
        } else if (tempEntry->column > j) {
            break;
        }
        moveNext(rowM);
    }

    // If x is not zero, create a new entry if no existing one
    if (x != 0) {
        Entry new = newEntry(j, x);
        if (index(rowM) >= 0) {
            insertBefore(rowM, new);
        } else {
            append(rowM, new);
        }
        M->NNZ++; // Increment NNZ for new non-zero entry
    }
}

// Matrix Arithmetic operations

Matrix copy(Matrix A){
	Matrix C = newMatrix(A->size);
	
	for (int i = 1; i <= A->size; i++) {
        	List rowsofA = A->rows[i];
        	moveFront(rowsofA);
        	
		while (index(rowsofA) >= 0) {
        		Entry entryA = (Entry)get(rowsofA);
            		changeEntry(C, i, entryA->column, entryA->value);
            		moveNext(rowsofA);
        	}

    	}
	C->NNZ = A->NNZ;
    	return C;
}


Matrix transpose(Matrix A){
	Matrix MT = newMatrix(A->size);
	
	for(int i = 1; i <= A->size; i++){
		List rowsofA = A->rows[i];
		moveFront(rowsofA);
		
		while(index(rowsofA) >= 0){
			Entry entryA = (Entry)get(rowsofA);
			changeEntry(MT, entryA->column, i, entryA->value);
			moveNext(rowsofA);
		}

	}
	MT->NNZ = A->NNZ;
	//printf("NNZ after transpose: %d\n", MT->NNZ);
	return MT;
}

Matrix scalarMult(double x, Matrix A){
	Matrix M = newMatrix(A->size);
    	
	if (x == 0){
		return M;
	}
	
	for (int i = 1; i <= A->size; i++) {
        	List rowsofA = A->rows[i];
        	moveFront(rowsofA);
        	
		while (index(rowsofA) >= 0) {
        		Entry entryA = (Entry)get(rowsofA);
            		changeEntry(M, i, entryA->column, x * (double) entryA->value);
            		moveNext(rowsofA);
        	}

    	}
	printf("mult %d\n", M->NNZ);
    	//printMatrix(stdout, M);
	return M;

}

Matrix sum(Matrix A, Matrix B){
	if(A->size != B->size){
		fprintf(stderr, "Matrix error: calling sum on matrices sizes that do not match\n");
		exit(EXIT_FAILURE);
	}

	Matrix S = newMatrix(A->size);
    	for (int i = 1; i <= A->size; i++) {
        	
		List rowsofA = A->rows[i];
        	List rowsofB = B->rows[i];
        	
		moveFront(rowsofA);
        	moveFront(rowsofB);
        	
		while (index(rowsofA) >= 0 || index(rowsofB) >= 0) {
            		if (index(rowsofA) >= 0 && index(rowsofB) >= 0) {

				Entry entryA = (Entry)get(rowsofA);
                		Entry entryB = (Entry)get(rowsofB);
                		
				if (entryA->column == entryB->column) {

					changeEntry(S, i, entryA->column, entryA->value + entryB->value);
                    			S->NNZ += 1;
					moveNext(rowsofA);
                    			moveNext(rowsofB);
				}

				else if (entryA->column < entryB->column) {
					changeEntry(S, i, entryA->column, entryA->value);
                    			S->NNZ -= 1;
					moveNext(rowsofA);
                		}

				else{
                    			changeEntry(S, i, entryB->column, entryB->value);
					moveNext(rowsofB);
                		}
            		}

			else if (index(rowsofA) >= 0) {
                		Entry entryA = (Entry)get(rowsofA);
                		changeEntry(S, i, entryA->column, entryA->value);
                		S->NNZ -= 1;
				moveNext(rowsofA);
            		}

			else {
                		Entry entryB = (Entry)get(rowsofB);
                		changeEntry(S, i, entryB->column, entryB->value);
				moveNext(rowsofB);
				
            		}
        	}
    	}
	printf("Sum nnz %d\n", S->NNZ);
    	return S;
}

Matrix diff(Matrix A, Matrix B){
    if (A->size != B->size) {
        fprintf(stderr, "Matrix error: calling diff on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

    Matrix diff = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List rowsofA = A->rows[i];
        List rowsofB = B->rows[i];
        moveFront(rowsofA);
        moveFront(rowsofB);

        while (index(rowsofA) >= 0 || index(rowsofB) >= 0) {
            if (index(rowsofA) >= 0 && index(rowsofB) >= 0) {
                Entry entryA = (Entry)get(rowsofA);
                Entry entryB = (Entry)get(rowsofB);

                if (entryA->column == entryB->column) {
                    double diffValue = entryA->value - entryB->value;
                    if (diffValue != 0) {
                        changeEntry(diff, i, entryA->column, diffValue);
                    }
                    moveNext(rowsofA);
                    moveNext(rowsofB);
                } else if (entryA->column < entryB->column) {
                    changeEntry(diff, i, entryA->column, entryA->value);
                    moveNext(rowsofA);
                } else {
                    changeEntry(diff, i, entryB->column, -entryB->value);
                    moveNext(rowsofB);
                }
            } else if (index(rowsofA) >= 0) {
                Entry entryA = (Entry)get(rowsofA);
                changeEntry(diff, i, entryA->column, entryA->value);
                moveNext(rowsofA);
            } else {
                Entry entryB = (Entry)get(rowsofB);
                changeEntry(diff, i, entryB->column, -entryB->value);
                moveNext(rowsofB);
            }
        }
    }
    return diff;
}


Matrix product(Matrix A, Matrix B){	
	Matrix P = newMatrix(A->size);
 	Matrix T = transpose(B);
    
    	for (int i = 1; i <= A->size; i++) {
		if (NNZ(A) == 0) continue;
        
        	for (int j = 1; j <= B->size; j++) {
            		double dotProd = vectorDot(A->rows[i], T->rows[j]);
            		if (dotProd != 0) {
                		changeEntry(P, i, j, dotProd);
            		}
        	}
    	}
    	freeMatrix(&T);
    	return P;
}

void printMatrix(FILE* out, Matrix M){
	for (int i = 1; i <= M->size; i++) {
        	List row = M->rows[i];
        	if (length(row) == 0) continue;

        	fprintf(out, "%d: ", i);
        	moveFront(row);
        	while (index(row) >= 0) {
            		Entry e = (Entry)get(row);
            		fprintf(out, "(%d, %.1f) ", e->column, e->value);
            		moveNext(row);
        	}
        	fprintf(out, "\n");
    	}
}