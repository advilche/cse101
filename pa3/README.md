#CSE 101 - Programming Assignment 2

#Overview
This project implements a Graph Abstract Data Type (ADT) in C and uses it to read a graph from an input file, process it, and print the adjacency list and strongly connected components.

#Files Submitted
- List.h: Header file defining the List ADT interface and function prototypes.
- List.c: Implementation of the List ADT, including all necessary functions for managing a doubly linked list.
- Graph.h: Header file defining the Graph ADT interface and function prototypes.
- Graph.c: Implementation of the Graph ADT, including all necessary functions for managing a graph.
- GraphTest.c: A test client for the Graph ADT.
- FindComponents.c: A main program for reading input, processing the graph, printing the adjacency list, and outputting strongly connected components.
- Makefile: Build script to compile the program and manage object files.
- README.md: This documentation file.

#Usage
To compile the program, use the following command:

# -> (bash)
make

# Fill in <input file> and <output file> with the specified files:
./FindComponents <input file> <output file>

#Alternatively, run the directory's tests (ensure permissions with chmod +x):

./../cse-101-public-tests/pa3/pa3.sh

#Example

#Input (input.txt)

30
13 30
7 28
...
7 30
0 0

#Running the Program

./FindComponents input.txt output.txt

#Output (output.txt)

Adjacency list representation of G:
1: ...
2: ...
...
30: ...

G contains X strongly connected components:
Component 1: ...
Component 2: ...
...
The output will include the adjacency list of the graph and a count of the strongly connected components, with each component printed in a readable format.

#Author
Adrian Vilchez
Student ID: 2000197