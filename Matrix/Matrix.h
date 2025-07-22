// --------------------------------------------------------------------
// Matrix.h
// Header file for Matrix ADT
// ---------------------------------------------------------------------

#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>

#include "List.h"

typedef struct EntryObj* Entry;
typedef struct MatrixObj* Matrix;

// --------------------------------------------------------------------

// newMatrix()
// Returns a reference to a new mXn Matrix object in the zero state.
Matrix newMatrix(int n, int m);

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);

// Access functions ----------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M);

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M);

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);

// Manipulation procedures --------------------------------------------

// sigmoidf
// Puts values through sigmoid function
Matrix sigmoid(Matrix M);

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations ---------------------------------------
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

List getRow(Matrix M, int i);  // controlled access to row[i]

List getColRow(Matrix M, int);   // turn col to row

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

double getEntry(Matrix M, int i, int j);

double vectorDot(List P, List Q);

double vectorSum(List P, List Q);


#endif // MATRIX_H_INCLUDE_