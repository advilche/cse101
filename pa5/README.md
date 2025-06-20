# CSE 101 - Programming Assignment 5

## Overview
In this assignment, you will implement a specialized integer List ADT in C++ that supports operations with a cursor concept. Using this List, you will implement a program to simulate and analyze the order of a perfect shuffle of a deck of cards. A perfect shuffle splits a deck into two halves and interleaves the cards alternately, mimicking a riffle shuffle. The goal is to determine how many perfect shuffles are required to return the deck to its original order for deck sizes ranging from 1 up to a specified maximum.

## Files Submitted
- **List.h**: Header file defining the List ADT interface and function prototypes.
- **List.cpp**: Implementation of the List ADT, including functions for managing a doubly linked list with a cursor.
- **ListTest.cpp**: A test client to ensure that the List ADT is implemented correctly.
- **Shuffle.cpp**: The main program that simulates and analyzes the order of perfect shuffles for different deck sizes.
- **Makefile**: Build script to compile the program and manage dependencies.
- **README.md**: Documentation for this project.

## Usage
- To compile and run the program, use the following commands:

### Compile
- make

## Execute
- ./Shuffle <max_deck_size>

## Example
- ./Shuffle 16

## Output
- The program will output a table indicating the number of perfect shuffles required to return the deck to its original order for deck sizes from 1 to <max_deck_size>. Example

deck size       shuffle count
------------------------------
 1               1
 2               2
 3               2
 4               4
 5               4
 6               3
 7               3
 8               6
 9               6
 10              10
 11              10
 12              12
 13              12
 14              4
 15              4
 16              8


# Bash script to test PA5
# Make sure you are in the correct directory
- make
- ./../cse-101-public-tests/pa5/pa5.sh

## Author 
- Adrian vilchez
- Student ID: 2000197