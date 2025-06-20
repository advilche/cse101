#include<iostream>
#include<fstream>
#include<string>

#include "Dictionary.h"

using namespace std;

int main(int argumentCount, char* argumentValues[]) {
      	ifstream inputFile;
      	ofstream outputFile;

      	if (argumentCount != 3) {
	    	cerr << "Usage: " << argumentValues[0] << " <input file> <output file>" << endl;
	    	return(EXIT_FAILURE);
      	}


      	inputFile.open(argumentValues[1]);
      	if (!inputFile.is_open()) {
	    	cerr << "Unable to open file " << argumentValues[1] << " for reading" << endl;
	    	return(EXIT_FAILURE);
      	}

	
      	outputFile.open(argumentValues[2]);

	if (!outputFile.is_open()) {
	    	cerr << "Unable to open file " << argumentValues[2] << " for writing" << endl;
	    	return(EXIT_FAILURE);
      	}

      	Dictionary dictionaryInstance;
      	string currentLine;

      	for (int lineNumber = 1; getline(inputFile, currentLine); lineNumber++) {
	    	dictionaryInstance.setValue(currentLine, lineNumber);
      	}

      	outputFile << dictionaryInstance << '\n'
   		<< dictionaryInstance.pre_string() << '\n';

      	return(EXIT_SUCCESS);
}