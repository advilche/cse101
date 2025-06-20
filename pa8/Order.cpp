#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check argument count

    	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
		return EXIT_FAILURE;
    	}

    // Open input file

    	ifstream inputFile(argv[1]);
    	if (!inputFile.is_open()) {
		cerr << "Error: Could not open input file " << argv[1] << endl;
		return EXIT_FAILURE;
    	}

    // Open output file

    	ofstream outputFile(argv[2]);
    	if (!outputFile.is_open()) {
		cerr << "Error: Could not open output file " << argv[2] << endl;
		return EXIT_FAILURE;
    	}

    // Create an instance of Dictionary

    	Dictionary dictionaryInstance;

    // Read lines from the input file
    //

    	string currentLine;
    	int lineNumber = 1;
    	while (getline(inputFile, currentLine)) {
		dictionaryInstance.setValue(currentLine, lineNumber);
		lineNumber++;
    	}

    // Write dictionary's string representation to the output file

    	outputFile << dictionaryInstance.to_string() << endl;

    // Write dictionary's pre-order string representation to the output file

    	outputFile << dictionaryInstance.pre_string() << endl;

    // Close files

    	inputFile.close();
    	outputFile.close();

    	return EXIT_SUCCESS;
}