#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "List.h"
#include "Matrix.h"

//typedef struct EntryObj* Entry;
//typedef struct MatrixObj* Matrix;
//typedef struct NeuralNetwork* NerualNetwork;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    int num_rows;
    int num_cols;
    int size;
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

// --------------------------------------------------------------------

// newMatrix()
Matrix newMatrix(int n, int m){
	Matrix newMatrix = malloc(sizeof(MatrixObj));

	newMatrix->num_rows = n;
	newMatrix->num_cols = m;
    newMatrix->size = n * m;
	newMatrix->rows = calloc(n + 1, sizeof(List));

	for (int i = 1; i <= n; i++) {
        	newMatrix->rows[i] = newList();
    	}

	return newMatrix;	
}

Matrix newRandMatrix(int n, int m, float min, float max){
	Matrix newMatrix = malloc(sizeof(MatrixObj));

	newMatrix->num_rows = n;
	newMatrix->num_cols = m;
    newMatrix->size = n * m;
	newMatrix->rows = calloc(n + 1, sizeof(List));

	for (int i = 1; i <= n; i++) {
        	newMatrix->rows[i] = newList();
    	}

    for (int i = 1; i <= n; i++){
        for (int j = 1;  j <= m; j++){
            changeEntry(newMatrix, i, j, randomInRange(min, max));
        }
    }

	return newMatrix;	
}

// freeMatrix()
void freeMatrix(Matrix* pM){
	if (pM != NULL && *pM != NULL) {
		for (int i = 1; i <= (*pM)->num_rows; i++) {
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

// Access functions ----------------------------------------------------

float randomInRange(int min, int max){
    float val = (float) rand() / (float) RAND_MAX;
    return min + val * (max - min);
}

// size()
int size(Matrix M) {
    return ( (M->num_rows)*(M->num_cols) );
}

// equals()
int equals(Matrix A, Matrix B);

// Manipulation procedures --------------------------------------------

// sigmoidf
double sigmoidf(double x){
    return 1.0f / (1.0f + expf(-x));
}

// sigmoid()
Matrix sigmoid(Matrix M){
    Matrix S = newMatrix(M->num_rows, M->num_cols);
    for (int i = 1; i <= M->num_rows; i++){
        for (int j = 1; j <= M->num_cols; j++){
            double val = getEntry(M, i, j);
            changeEntry(S, i, j, sigmoidf(val));
        }
    }

    return S;
}

// makeZero()
void makeZero(Matrix M){
	for (int i = 1; i <= M->size; i++) {
        List rowM = M->rows[i];
        moveFront(rowM);
        while (index(rowM) >= 0){
            Entry tempEntry = (Entry)get(rowM);
            freeEntry(&tempEntry);
            moveNext(rowM);
        }
        clear(rowM);
    }
    M->num_cols = 0;
    M->num_rows = 0;
}

// changeEntry()
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
//                M->NNZ--;
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
//        M->NNZ++; // Increment NNZ for new non-zero entry
    }
}

// Matrix Arithmetic operations ---------------------------------------
// copy()
Matrix copy(Matrix A);

// transpose()
Matrix transpose(Matrix A){
    Matrix M = newMatrix(A->num_cols, A->num_rows);

    for (int i = 1; i <= A->num_rows; i++) {
        List tempList = A->rows[i];
        moveFront(tempList);

        while (index(tempList) >= 0) {
            Entry tempE = (Entry)get(tempList);
            
            changeEntry(M, tempE->column, i, tempE->value);
            moveNext(tempList);
        }
    }

    return M;
}

// scalarMult()
Matrix scalarMult(double x, Matrix A){
    Matrix S = newMatrix(A->num_rows, A->num_cols);

    for (int i = 1; i <= A->num_rows; i++){
        for (int j = 1; j <= A->num_cols; j++){
            double eVal = getEntry(A, i, j);
            changeEntry(S, i, j, eVal * x);
        }
    }

    return S;
}

// sum()
Matrix sum(Matrix A, Matrix B){
    if (A->num_cols != B->num_cols || A->num_rows != B->num_rows){
        fprintf(stderr, "sum: invalid shape, colsA = (%d) != colsB = (%d) || rowsA = (%d) != rowsB = (%d)", A->num_cols, B->num_cols, A->num_rows, B->num_rows);
    }

    Matrix S = newMatrix(A->num_rows, B->num_cols);
        for (int i = 1; i <= A->num_rows; i++){
            for (int j = 1; j <= B->num_cols; j++){
                double Aij = getEntry(A, i, j);
                double Bij = getEntry(B, i, j);
                changeEntry(S, i, j, Aij + Bij);
            }
        }

    return S;
}

// diff()
Matrix diff(Matrix A, Matrix B);

// product()
Matrix product(Matrix A, Matrix B){
    if (A->num_cols != B->num_rows){
        fprintf(stderr, "product: invalid shape (%d, %d)\n", A->num_cols, B->num_rows);
    }

    Matrix P = newMatrix(A->num_rows, B->num_cols);
    for (int i = 1; i <= A->num_rows; i++){
        for (int j = 1; j <= B->num_cols; j++){
            List rowiA = A->rows[i];
            List coljB = getColRow(B, j);
            double dotProd = vectorDot(rowiA, coljB);
            changeEntry(P, i, j, dotProd);
        }
    }

    return P;
}

// printMatrix()
void printMatrix(FILE* out, Matrix M){
	for (int i = 1; i <= M->num_rows; i++) {
        	List row = M->rows[i];
        	if (length(row) == 0) continue;
            
        	fprintf(out, "%d: ", i);
        	moveFront(row);
        	while (index(row) >= 0) {
            		Entry e = (Entry)get(row);
                    if (isInteger(e->value)){
                        fprintf(out, "(%d, %1.0g) ", e->column, e->value);
                    } else {
                        fprintf(out, "(%d, %.8g) ", e->column, e->value);
                    }
            		moveNext(row);
        	}
        	fprintf(out, "\n");
    	}
}

// isInteger()
int isInteger(float num) {
    return (num == (int) num); 
}

// getEntry()
double getEntry(Matrix M, int i, int j){
    if (M->num_rows < i || M->num_cols < j){
        fprintf(stderr, "getEntry: invalid index (%d, %d)\n", i, j);
        exit(EXIT_FAILURE);
    }

    List rowM = M->rows[i];
    moveFront(rowM);

    while (index(rowM) >= 0) {
        Entry e = (Entry)get(rowM);
        if (e->column == j) {
            return e->value;
        }
        moveNext(rowM);
    }

    return 0.0; // If not found, treat as zero
}

// vectorDot()
double vectorDot(List P, List Q){
    if (length(P) != length(Q)){
        fprintf(stderr, "vectorDot: invalid shape (%d, %d)\n", length(P), length(Q));
        exit(EXIT_FAILURE);
    }

    moveFront(P);
    moveFront(Q);

    double total = 0;

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry eP = (Entry)get(P);
        Entry eQ = (Entry)get(Q);

        if (eP->column == eQ->column) {
            total += eP->value * eQ->value;
            moveNext(P);
            moveNext(Q);
        } else if (eP->column < eQ->column) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }

    return total;
}

// getRow()
List getRow(Matrix M, int i) {
    return M->rows[i];
}

// getColRow()
List getColRow(Matrix M, int j){
    List newL = newList();  // allocate new list for column j as a row

    for (int k = 1; k <= M->num_rows; k++) {  // matrix is 1-indexed
        List tempList = M->rows[k];
        moveFront(tempList);

        while (index(tempList) >= 0) {
            Entry ek = (Entry)get(tempList);
            if (ek->column == j) {
                // Create a copy of the entry to avoid aliasing
                Entry newE = newEntry(k, ek->value);  // column ← row index
                append(newL, newE);
                break; // only one entry per column in each row
            }
            moveNext(tempList);
        }
    }

    return newL;
}

// vectorSum()
double vectorSum(List P, List Q);


//#endif // MATRIX_H_INCLUDE_