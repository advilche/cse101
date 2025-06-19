# CSE 101 - Programming Assignment 4

## Overview
In this assignment, you will implement a sparse matrix calculator using a specialized data structure that exploits the sparseness of matrix operands. The program will efficiently perform matrix operations such as addition, multiplication, scalar multiplication, transposition, and others, taking advantage of sparse matrices where most elements are zero. By using a space-efficient representation with lists to store non-zero matrix entries, the program will be capable of handling large matrices more effectively than traditional dense matrix representations.

## Files Submitted
- **List.h**: Header file defining the List ADT interface and function prototypes.
- **List.c**: Implementation of the List ADT, including necessary functions for managing a list of generic pointers (modified from PA1).
- **Matrix.h**: Header file defining the Matrix ADT interface and function prototypes.
- **Matrix.c**: Implementation of the Matrix ADT, including operations on sparse matrices such as multiplication, addition, and transposition.
- **Sparse.c**: The main program that reads input matrices, performs matrix operations, and writes the output to a file.
- **ListTest.c**: A test client to ensure that the List ADT works correctly.
- **MatrixTest.c**: A test client to ensure that the Matrix ADT works correctly.
- **README.md**: Documentation for this project.
- **Makefile**: Build script to compile the program and manage object files.

## Usage
To compile the program, use the following command:

```bash
make

./Sparse <input file> <output file>

./../cse-101-public-tests/pa4/pa4.sh

##EXAMPLE

3 9 5
1 1 1.0
1 2 2.0
1 3 3.0
2 1 4.0
2 2 5.0
2 3 6.0
3 1 7.0
3 2 8.0
3 3 9.0

1 1 1.0
1 3 1.0
3 1 1.0
3 2 1.0
3 3 1.0

./Sparse input.txt output.txt

A has 9 non-zero entries:
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

B has 5 non-zero entries:
1: (1, 1.0) (3, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

(1.5)*A =
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

A+B =
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

A+A =
1: (1, 2.0) (2, 4.0) (3, 6.0)
2: (1, 8.0) (2, 10.0) (3, 12.0)
3: (1, 14.0) (2, 16.0) (3, 18.0)

B-A =
1: (2, -2.0) (3, -2.0)
2: (1, -4.0) (2, -5.0) (3, -6.0)
3: (1, -6.0) (2, -7.0) (3, -8.0)

A-A =

Transpose(A) =
1: (1, 1.0) (2, 4.0) (3, 7.0)
2: (1, 2.0) (2, 5.0) (3, 8.0)
3: (1, 3.0) (2, 6.0) (3, 9.0)

A*B =
1: (1, 4.0) (2, 3.0) (3, 4.0)
2: (1, 10.0) (2, 6.0) (3, 10.0)
3: (1, 16.0) (2, 9.0) (3, 16.0)

B*B =
1: (1, 2.0) (2, 1.0) (3, 2.0)
3: (1, 2.0) (2, 1.0) (3, 2.0)

#Author
Adrian Vilchez
Student ID: 2000197

#