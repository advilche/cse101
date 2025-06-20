#include <iostream>
#include <cassert>
#include "Dictionary.h"

using namespace std;

int main() {
    	Dictionary dict;

	// Test 1: Insert key-value pairs and size()
 
	dict.setValue("apple", 1);
    	dict.setValue("banana", 2);
    	dict.setValue("cherry", 3);
    	assert(dict.size() == 3);
    	cout << "Test 1 Passed: size() works after insertions." << endl;

    	// Test 2: Check contains() method

    	assert(dict.contains("apple"));
    	assert(dict.contains("banana"));
    	assert(dict.contains("cherry"));
    	assert(!dict.contains("date"));
    	cout << "Test 2 Passed: contains() works." << endl;

    	// Test 3: getValue() method

    	assert(dict.getValue("apple") == 1);
    	assert(dict.getValue("banana") == 2);
    	assert(dict.getValue("cherry") == 3);
    	cout << "Test 3 Passed: getValue() works." << endl;

	// Test 4: Update value of existing key

    	dict.setValue("banana", 5);
    	assert(dict.getValue("banana") == 5);
    	cout << "Test 4 Passed: setValue() updates existing keys correctly." << endl;

    	// Test 5: Remove keys and verify size

    	dict.remove("banana");
    	assert(dict.size() == 2);
    	assert(!dict.contains("banana"));
    	cout << "Test 5 Passed: remove() works." << endl;

     	// Test 6: Test begin(), end(), next(), prev()

    	dict.begin();
    	assert(dict.currentKey() == "apple");
    	dict.next();
    	assert(dict.currentKey() == "cherry");
    	dict.prev();
    	assert(dict.currentKey() == "apple");
    	cout << "Test 6 Passed: Iteration (begin, end, next, prev) works." << endl;


    	// Test 7: clear() method

    	dict.clear();
    	assert(dict.size() == 0);
    	assert(!dict.hasCurrent());
    	cout << "Test 7 Passed: clear() works." << endl;


    	// Test 8: to_string() and pre_string()

    	dict.setValue("grape", 10);
    	dict.setValue("orange", 20);
    	dict.setValue("kiwi", 30);
    	string inOrder = dict.to_string();
    	string preOrder = dict.pre_string();
    	assert(!inOrder.empty());
    	assert(!preOrder.empty());
    	cout << "Test 8 Passed: to_string() and pre_string() generate strings." << endl;


    	// Test 9: equals() and operator==

    	Dictionary dict2;
    	dict2.setValue("grape", 10);
    	dict2.setValue("orange", 20);
    	dict2.setValue("kiwi", 30);
    	assert(dict.equals(dict2));
    	assert(dict == dict2);
    	cout << "Test 9 Passed: equals() and operator== work." << endl;

    	cout << "All tests passed successfully." << endl;

    	return 0;
}
