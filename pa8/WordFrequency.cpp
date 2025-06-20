#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check command-line arguments

    	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return EXIT_FAILURE;
    	}


    	string inputFile = argv[1];
    	string outputFile = argv[2];

    // Open the input file

    	ifstream in(inputFile);
    	if (!in.is_open()) {
		cerr << "Error: Could not open file " << inputFile << endl;
		return EXIT_FAILURE;
    	}

    // Open the output file

    	ofstream out(outputFile);
    	if (!out.is_open()) {
		cerr << "Error: Could not open file " << outputFile << endl;
		return EXIT_FAILURE;
    	}

    // Create a Dictionary to store word frequencies

    	Dictionary wordFreq;

    // Define delimiters for tokenization

    	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    	string line;
    	while (getline(in, line)) {
		size_t start = line.find_first_not_of(delim);
		while (start != string::npos) {
	    		size_t end = line.find_first_of(delim, start);
	    		string word = line.substr(start, end - start);

            // Convert the word to lowercase

	    		for (char& c : word) {
				c = tolower(c);
	    		}

            // Update the frequency in the Dictionary

	    		if (wordFreq.contains(word)) {
				wordFreq.setValue(word, wordFreq.getValue(word) + 1);
	    		} else {
				wordFreq.setValue(word, 1);
	    		}

	    		start = line.find_first_not_of(delim, end);
		}
    	}

    // Write the Dictionary contents to the output file

    	out << wordFreq.to_string();

    // Close files

    	in.close();
    	out.close();
    	return EXIT_SUCCESS;
}