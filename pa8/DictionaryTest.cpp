#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main() {
    	Dictionary dict;

    // Test 1: Insert elements into the dictionary

	cout << "Test 1: Inserting elements into the dictionary" << endl;
    	dict.setValue("alpha", 1);
  //  	dict.setValue("beta", 2);
    	dict.setValue("gamma", 3);
//    	dict.setValue("delta", 4);


    	cout << "In-order string representation:" << endl;
    	cout << dict.to_string() << endl;

    // Test 2: Check if the dictionary contains a key

    	cout << "Test 2: Checking contains function" << endl;
    	cout << "Contains 'beta'? " << (dict.contains("beta") ? "Yes" : "No") << endl;
    	cout << "Contains 'epsilon'? " << (dict.contains("epsilon") ? "Yes" : "No") << endl;

    // Test 3: Get value associated with a key

    	cout << "Test 3: Getting values" << endl;
    	cout << "Value for 'gamma': " << dict.getValue("gamma") << endl;

    // Test 4: Delete an element and check the dictionary

    	cout << "Test 4: Removing 'beta' from the dictionary" << endl;
    	dict.remove("beta");
    	cout << "Dictionary after removal:" << endl;
    	cout << dict.to_string() << endl;

    // Test 5: Use iterators to traverse the dictionary

    	cout << "Test 5: Using iterators" << endl;
    	dict.begin();
    	cout << "Starting from the smallest key: " << dict.currentKey() << " : " << dict.currentVal() << endl;
    	while (dict.hasCurrent()) {
    	    cout << dict.currentKey() << " : " << dict.currentVal() << endl;
    	    dict.next();
    	}

    // Test 6: Test pre-order string representation

    	cout << "Test 6: Pre-order string representation" << endl;
    	cout << dict.pre_string() << endl;

    // Test 7: Clear the dictionary and check its state

    	cout << "Test 7: Clearing the dictionary" << endl;
    	dict.clear();
    	cout << "Dictionary size after clearing: " << dict.size() << endl;
    	cout << "Dictionary content after clearing:" << endl;
    	cout << dict.to_string() << endl;

    // Test 8: Copy constructor and assignment operator

    	cout << "Test 8: Copying and assigning dictionaries" << endl;
    	dict.setValue("epsilon", 5);
    	dict.setValue("zeta", 6);
    	Dictionary dictCopy = dict; // Copy constructor
    	Dictionary dictAssigned;
    	dictAssigned = dict; // Assignment operator

    	cout << "Original Dictionary:" << endl;
    	cout << dict.to_string() << endl;
    	cout << "Copied Dictionary:" << endl;
    	cout << dictCopy.to_string() << endl;
    	cout << "Assigned Dictionary:" << endl;
    	cout << dictAssigned.to_string() << endl;

    	return 0;
}