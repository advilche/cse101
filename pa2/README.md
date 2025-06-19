# CSE 101 - Programming Assignment 2

# Overview
This project implements an Integer List Abstract Data Type (ADT) in C and uses it to alphabetize lines from an input file.

# Files Submitted
- List.h: Header file defining the List ADT interface and function prototypes.
- List.c: Implementation of the List ADT, including all necessary functions for managing a doubly linked list.
- Graph.h: Header file defining the Graph ADT interface and function prototypes.
- Graph.c: Implementation of the Graph ADT, including all necessary functions for managing a graph.
- GraphTest.c: A test client for the Graph ADT.
- FindPath.c: A main program for reading input, processing graph, printing adjacency list, and writing all paths to output.
- Makefile: Build script to compile the program and manage object files.
- README.md: This documentation file.

# Usage
To compile the program, use the following command:

#-> (bash)
make

# fill in <input file> and <output file> with specefied files
/.FindPath <input file> <output file>

# -> or to run with the directory's tests with permisions chmod +x
./../cse-101-public-tests/pa1/pa1.sh

# EXAMPLE

# input.txt
30
13 30
7 28
7 21
26 6
9 15
23 18
14 13
19 26
18 20
14 7
13 1
20 10
30 23
11 16
17 29
23 17
15 28
14 5
10 8
17 30
9 21
8 12
14 3
21 28
29 3
7 12
27 7
5 15
17 6
17 27
21 18
8 3
9 2
17 10
27 14
25 17
13 24
17 14
29 9
14 16
26 29
18 29
30 20
3 25
13 11
15 19
13 18
2 26
27 22
18 8
2 12
6 14
2 6
19 24
30 14
5 10
29 19
1 18
2 15
11 22
14 9
5 21
8 22
27 1
7 18
22 23
26 10
11 5
15 7
10 19
20 5
24 1
16 2
4 19
12 15
22 25
1 23
11 4
9 18
28 10
14 8
21 14
29 15
8 16
23 20
3 5
20 14
22 2
17 28
28 2
23 16
9 22
18 26
4 16
28 12
28 9
21 17
22 14
30 9
20 28
5 28
12 4
22 12
23 11
7 8
13 23
27 16
12 11
15 25
21 16
23 6
25 12
24 18
19 23
19 5
16 24
3 7
17 4
30 19
28 14
16 18
21 13
18 6
29 13
30 22
25 21
17 19
21 23
24 29
1 6
15 27
11 1
1 4
25 13
27 6
20 9
6 11
5 9
27 24
12 9
25 2
17 2
29 4
28 24
20 2
4 18
29 21
8 21
4 7
28 13
23 27
25 28
25 30
3 4
23 29
16 12
29 6
15 4
13 26
20 24
27 2
8 28
3 19
9 17
25 4
20 8
2 29
14 15
9 27
20 12
20 13
23 24
10 25
9 19
25 5
19 11
12 24
30 5
21 22
25 9
20 21
28 11
24 8
18 14
14 11
18 5
25 23
24 5
24 7
14 4
17 20
9 13
17 15
10 6
30 18
10 16
10 24
16 28
7 5
7 30
0 0
15 24
21 21
27 15
1 23
13 30
19 17
12 1
23 15
7 2
20 6
13 20
5 28
0 0


# running
./FindPath input.txt output.txt

# output.txt will show up as
1: 4 6 11 13 18 23 24 27
2: 6 9 12 15 16 17 20 22 25 26 27 28 29
3: 4 5 7 8 14 19 25 29
4: 1 3 7 11 12 14 15 16 17 18 19 25 29
5: 3 7 9 10 11 14 15 18 19 20 21 24 25 28 30
6: 1 2 10 11 14 17 18 23 26 27 29
7: 3 4 5 8 12 14 15 18 21 24 27 28 30
8: 3 7 10 12 14 16 18 20 21 22 24 28
9: 2 5 12 13 14 15 17 18 19 20 21 22 25 27 28 29 30
10: 5 6 8 16 17 19 20 24 25 26 28
11: 1 4 5 6 12 13 14 16 19 22 23 28
12: 2 4 7 8 9 11 15 16 20 22 24 25 28
13: 1 9 11 14 18 20 21 23 24 25 26 28 29 30
14: 3 4 5 6 7 8 9 11 13 15 16 17 18 20 21 22 27 28 30
15: 2 4 5 7 9 12 14 17 19 25 27 28 29
16: 2 4 8 10 11 12 14 18 21 23 24 27 28
17: 2 4 6 9 10 14 15 19 20 21 23 25 27 28 29 30
18: 1 4 5 6 7 8 9 13 14 16 20 21 23 24 26 29 30
19: 3 4 5 9 10 11 15 17 23 24 26 29 30
20: 2 5 8 9 10 12 13 14 17 18 21 23 24 28 30
21: 5 7 8 9 13 14 16 17 18 20 22 23 25 28 29
22: 2 8 9 11 12 14 21 23 25 27 30
23: 1 6 11 13 16 17 18 19 20 21 22 24 25 27 29 30
24: 1 5 7 8 10 12 13 16 18 19 20 23 27 28 29
25: 2 3 4 5 9 10 12 13 15 17 21 22 23 28 30
26: 2 6 10 13 18 19 29
27: 1 2 6 7 9 14 15 16 17 22 23 24
28: 2 5 7 8 9 10 11 12 13 14 15 16 17 20 21 24 25
29: 2 3 4 6 9 13 15 17 18 19 21 23 24 26
30: 5 7 9 13 14 17 18 19 20 22 23 25

The distance from 15 to 24 is 2
A shortest 15-24 path is: 15 5 24

The distance from 21 to 21 is 0
A shortest 21-21 path is: 21

The distance from 27 to 15 is 1
A shortest 27-15 path is: 27 15

The distance from 1 to 23 is 1
A shortest 1-23 path is: 1 23

The distance from 13 to 30 is 1
A shortest 13-30 path is: 13 30

The distance from 19 to 17 is 1
A shortest 19-17 path is: 19 17

The distance from 12 to 1 is 2
A shortest 12-1 path is: 12 4 1

The distance from 23 to 15 is 2
A shortest 23-15 path is: 23 17 15

The distance from 7 to 2 is 2
A shortest 7-2 path is: 7 12 2

The distance from 20 to 6 is 2
A shortest 20-6 path is: 20 2 6

The distance from 13 to 20 is 1
A shortest 13-20 path is: 13 20

The distance from 5 to 28 is 1
A shortest 5-28 path is: 5 28

Adrian Vilchez
2000197