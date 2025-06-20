# CSE 101 - Lab 7

## Overview
In this lab, I worked with a Dictionary ADT that was implemented in C++ to perform operations of the keyValue pairs which were stored in a binary search tree (BST). The program reads a series of string from a given input file, it then associates each string with an integer. The outputs are traversals of the BST. This lab added to my understanding of a BST, iterator, and C++ in general.

## Files Submitted 
- **README.md: 		written by me, documentation for the lab
- **Makefile: 		Building script to compile the program and all its respective dependencies
- **Dictionary.h: 	Header file defining the prototypes for the Dictionary ADT
- **Dictionary.cpp:	Implementation of the Dictionary ADT, as well as the appropriate methods
- **DictionaryTest.cpp:	A test program that acts as a fail net for testing and compliling
- **Order.cpp:		Final top client program to process input files and dictionary

## Usage 
- to compile the program, use the following

### Compile
- make

### Execute
- ./order <input_file> <output_file>

##input format
- one string per line

##Example input
- apple
- banana
- date
- .
- .
- .

##Example output
- In-Order Traversal:
- apple: 1
- banana: 1
- date: 1
- .
- .
- .

- Pre-Order Traversal:
- apple
- banana
- date
- .
- .
- .

### Explanation of Output
1. In-Order traversal:
	- Lists the keyValue pairs in alphabetical order of the keys
2. Pre-Order traversal:
	- Lists only the keys in pre-order traversal of the BST


### Author
- Adrian Vilchez
- ID: 2000197