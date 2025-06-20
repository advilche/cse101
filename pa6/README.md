# CSE 101 - Lab 6

## Overview
In this lab, I worked with a BigInteger ADT implemented in C++ to perform arithmetic operations on arbitrarily large integers. I implement a program that uses this ADT to read two large integers from a file, perform various arithmetic operations on them, and write the results to an output file. This lab deepened my  understanding of object-oriented programming concepts and algorithmic implementation in C++.

## Files Submitted
- **BigInteger.h**: Header file defining the BigInteger ADT interface and function prototypes.
- **BigInteger.cpp**: Implementation of the BigInteger ADT, including methods for addition, subtraction, multiplication, and other operations.
- **Arithmetic.cpp**: The main program that reads two large integers from an input file, performs arithmetic operations, and writes the results to an output file.
- **Makefile**: Build script to compile the program and manage dependencies.
- **README.md**: Documentation for this lab.

## Usage
- To compile and run the program, use the following commands:

### Compile
- make

### Execute
- ./Arithmetic <input_file> <output_file>

### Input Format
- The input file must contain two large integers, each on its own line.

### Example Input (input.txt)
123456789012345678901234567890 987654321098765432109876543210


### Example Output (output.txt)
123456789012345678901234567890

987654321098765432109876543210

1111111110111111111011111111100

-864197532086419753208641975320

0

-1728395061728395061728395061720

1219326313565005315910684315811263526900

15241578753238836750495351562536198787501905199875019052100

97546105789810324390578126336512670556819598413934470522900

1350851717672992080628961669283906140070


### Explanation of Output
1. The first two numbers are the integers read from the input file.
2. The subsequent results correspond to various arithmetic operations performed on the integers:
   - Addition
   - Subtraction
   - Subtraction of the number from itself
   - Multiplication of the first number by 3 minus the second number multiplied by 2
   - Multiplication of the two numbers
   - Square of the first number
   - Square of the second number
   - Complex polynomial expression involving powers of the numbers.

## Bash script to test Lab 6
- Make sure you are in the correct directory:

# make
- ./../cse-101-public-tests/lab6/lab6.sh

### Author
- Adrian Vilchez
- StudentID: 2000197

```bash