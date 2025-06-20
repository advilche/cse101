# CSE 101 - Lab 8

## Overview
In this lab, I worked with a Dictionary ADT that was implemented in C++ using a Red-Black Tree (RBT) as the underlying data structure. The program reads a series of words from a given input file and associates each word with a line number. The outputs include two types of tree traversals (in-order and pre-order) of the Red-Black Tree. This lab enhanced my understanding of Red-Black Trees, tree rotations, and C++ programming techniques related to data structures.

## Files Submitted
- **README.md**: Documentation for the lab written by me
- **Makefile**: Build script to compile the program and all its dependencies
- **Dictionary.h**: Header file defining the prototypes for the Dictionary ADT using Red-Black Tree
- **Dictionary.cpp**: Implementation of the Dictionary ADT and necessary methods
- **WordFrequency.cpp**: Client program that reads a text file and counts the frequency of words using the Dictionary
- **DictionaryClient.cpp**: A simple client program to test the Dictionary ADT
- **Shakespeare.txt / Gutenberg.txt**: Sample input files to test the WordFrequency program
- **Shakespeare-out.txt / Gutenberg-out.txt**: Expected output files

## Usage

### Compile
To compile the program, use the following command:


'''bash

make

## Execute
- ./WordFrequency <input_file> <output_file>

## Example
Hello, world! Hello everyone.
This is a test. A simple test.

## Example Output
- in-order
a : 2
everyone : 1
hello : 2
is : 1
simple : 1
test : 2
this : 1
world : 1

- pre-order
a
everyone
hello
is
simple
test
this
world

## Author
- Adrian Vilchez
- 2000197