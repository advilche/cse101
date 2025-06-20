#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
      	ifstream inputFile;
      	ofstream outputFile;

      	if (argc != 3) {
	    	cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
	    	return(EXIT_FAILURE);
      	}


      	inputFile.open(argv[1]);
      	if (!inputFile.is_open()) {

      	  cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      	  return(EXIT_FAILURE);
      	}


      	outputFile.open(argv[2]);
      	if (!outputFile.is_open()) {
	    	cerr << "Unable to open file " << argv[2] << " for writing" << endl;
	    	return(EXIT_FAILURE);
      	}


      	string num1, num2;
      	inputFile >> num1 >> num2;
      
	BigInteger bigInt1(num1), bigInt2(num2);
      	const BigInteger constant3("3"), constant2("2"), constant9("9"), constant16("16");

      	outputFile << bigInt1 << '\n' << '\n'
   		<< bigInt2 << '\n' << '\n'
   		<< bigInt1 + bigInt2 << '\n' << '\n'
   		<< bigInt1 - bigInt2 << '\n' << '\n'
   		<< bigInt1 - bigInt1 << '\n' << '\n'
   		<< bigInt1.mult(constant3) - bigInt2.mult(constant2) << '\n' << '\n'
   		<< bigInt1 * bigInt2 << '\n' << '\n'
   		<< bigInt1 * bigInt1 << '\n' << '\n'
   		<< bigInt2 * bigInt2 << '\n' << '\n'
   		<< constant9 * bigInt1 * bigInt1 * bigInt1 * bigInt1 
   		+ constant16 * bigInt2 * bigInt2 * bigInt2 * bigInt2 * bigInt2 << '\n';

  inputFile.close();
  outputFile.close();

  return(EXIT_SUCCESS);
}
