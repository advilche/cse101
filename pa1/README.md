# CSE 101 - Programming Assignment 1

# Overview
This project implements an Integer List Abstract Data Type (ADT) in C and uses it to alphabetize lines from an input file.

# Files Submitted
- List.h: Header file defining the List ADT interface and function prototypes.
- List.c: Implementation of the List ADT, including all necessary functions for managing a doubly linked list.
- ListTest.c: A test client for the List ADT that verifies the correctness of its operations.
- Lex.c: Main program for reading input, sorting lines, and writing output.
- Makefile: Build script to compile the program and manage object files.
- README.md: This documentation file.

# Usage
To compile the program, use the following command:

#-> (bash)
make

# fill in <input file> and <output file> with specefied files
/.Lex <input file> <output file>

# -> or to run with the directory's tests with permisions chmod +x
./../cse-101-public-tests/pa1/pa1.sh

# EXAMPLE

# input.txt
one
two
three
four 
five

# running
./Lex input.txt output.txt

# output.txt will show up as
five
four
one 
three
two

Adrian Vilchez
2000197