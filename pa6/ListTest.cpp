#include <iostream>
#include <cassert>
#include "List.h"  // Update the path to your List.h file

using namespace std;

// Function prototypes for each test
void testEmptySize();
void testInsertAfterSize();
void testInsertBeforeSize();
void testEraseAfterSize();
void testEraseBeforeSize();
void testConcatSize();
void testCleanupSize();
void testMoveFrontPosition();
void testMoveBackPosition();
void testMoveNextPosition();
void testMovePrevPosition();
void testFindNextPosition();
void testFindPrevPosition();
void testEraseAfterPosition();
void testEraseBeforePosition();
void testConcatPosition();

int main() {
    cout << "Running Tests..." << endl;

    // Running each test
    testEmptySize();
    testInsertAfterSize();
    testInsertBeforeSize();
    testEraseAfterSize();
    testEraseBeforeSize();
    testConcatSize();
    testCleanupSize();
    testMoveFrontPosition();
    testMoveBackPosition();
    testMoveNextPosition();
    testMovePrevPosition();
    testFindNextPosition();
    testFindPrevPosition();
    testEraseAfterPosition();
    testEraseBeforePosition();
    testConcatPosition();

    cout << "All Tests Passed!" << endl;

    return 0;
}

void testEmptySize() {
    List A;
    assert(A.length() == 0);  // Expecting the list to be empty initially
    cout << "Test Empty_size PASSED" << endl;
}

void testInsertAfterSize() {
    List A;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);
    assert(A.length() == 5);  // Expecting length of 5
    cout << "Test InsertAfter_size PASSED" << endl;
}

void testInsertBeforeSize() {
    List A;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);
    assert(A.length() == 5);  // Expecting length of 5
    cout << "Test InsertBefore_size PASSED" << endl;
}

void testEraseAfterSize() {
    List A;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(5);
    A.insertBefore(12);

    A.movePrev();
    A.eraseAfter();
    assert(A.length() == 4);  // Expecting length of 4 after erasing one element

    A.findPrev(2);
    A.eraseAfter();
    assert(A.length() == 3);  // Expecting length of 3 after erasing another element

    cout << "Test EraseAfter_size PASSED" << endl;
}

void testEraseBeforeSize() {
    List A;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(12);

    A.moveNext();
    A.eraseBefore();
    assert(A.length() == 4);  // Expecting length of 4 after erasing one element

    A.findNext(2);
    A.eraseBefore();
    assert(A.length() == 3);  // Expecting length of 3 after erasing another element

    cout << "Test EraseBefore_size PASSED" << endl;
}

void testConcatSize() {
    List A, B, C;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    C = A.concat(B);
    assert(C.length() == 6);  // Expecting length of 6 after concatenation
    cout << "Test Concat_size PASSED" << endl;
}

void testCleanupSize() {
    List A;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(1);
    A.cleanup();
    assert(A.length() == 3);  // Expecting length of 3 after cleanup
    cout << "Test Cleanup_size PASSED" << endl;
}

void testMoveFrontPosition() {
    List A;
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(3214);
    A.moveFront();
    assert(A.position() == 0);  // Expecting position 0
    cout << "Test MoveFront_position PASSED" << endl;
}

void testMoveBackPosition() {
    List A;
    A.insertAfter(1);
    A.insertAfter(5);
    A.insertAfter(16);
    A.insertAfter(176);
    A.insertAfter(3214);
    A.moveBack();
    assert(A.position() == 5);  // Expecting position 5
    cout << "Test MoveBack_position PASSED" << endl;
}

void testMoveNextPosition() {
    List A;
    A.insertAfter(3214);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    A.moveNext();
    A.moveNext();
    assert(A.position() == 2);  // Expecting position 2
    A.moveNext();
    A.moveNext();
    A.moveNext();
    assert(A.position() == 5);  // Expecting position 5
    cout << "Test MoveNext_position PASSED" << endl;
}

void testMovePrevPosition() {
    List A;
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(3214);
    A.movePrev();
    A.movePrev();
    assert(A.position() == 3);  // Expecting position 3
    A.movePrev();
    A.movePrev();
    A.movePrev();
    assert(A.position() == 0);  // Expecting position 0
    cout << "Test MovePrev_position PASSED" << endl;
}

void testFindNextPosition() {
    List A;
    A.insertAfter(16);
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(16);
    A.insertAfter(5);
    A.insertAfter(1);
    A.findNext(16);
    assert(A.position() == 3);  // Expecting position 3
    A.movePrev();
    A.insertBefore(225);
    assert(A.position() == 3);  // Expecting position 3 after inserting
    A.moveNext();
    A.findNext(16);
    assert(A.position() == 7);  // Expecting position 7
    cout << "Test FindNext_position PASSED" << endl;
}

void testFindPrevPosition() {
    List A;
    A.insertBefore(1);
    A.insertBefore(5);
    A.insertBefore(16);
    A.insertBefore(176);
    A.insertBefore(200);
    A.insertBefore(16);
    A.findPrev(16);
    assert(A.position() == 5);  // Expecting position 5
    A.moveNext();
    A.insertAfter(225);
    assert(A.position() == 6);  // Expecting position 6
    A.movePrev();
    A.findPrev(16);
    assert(A.position() == 2);  // Expecting position 2
    cout << "Test FindPrev_position PASSED" << endl;
}

void testEraseAfterPosition() {
    List A;
    A.insertAfter(200);
    A.insertAfter(176);
    A.insertAfter(15);
    A.insertAfter(10);
    A.insertAfter(5);
    A.findNext(15);
    A.eraseAfter();
    assert(A.position() == 3);  // Expecting position 3 after erasing
    A.insertAfter(175);
    A.eraseAfter();
    assert(A.position() == 3);  // Expecting position 3 after erasing again
    cout << "Test EraseAfter_position PASSED" << endl;
}

void testEraseBeforePosition() {
    List A;
    A.insertBefore(5);
    A.insertBefore(10);
    A.insertBefore(15);
    A.insertBefore(176);
    A.insertBefore(200);
    A.findPrev(15);
    A.eraseBefore();
    assert(A.position() == 1);  // Expecting position 1
    A.insertAfter(175);
    A.eraseBefore();
    assert(A.position() == 0);  // Expecting position 0 after erasing
    cout << "Test EraseBefore_position PASSED" << endl;
}

void testConcatPosition() {
    List A, B;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    B.insertBefore(4);
    B.insertBefore(5);
    B.insertBefore(6);

    List C = A.concat(B);
    assert(C.position() == 0);  // Expecting position 0 after concatenation
    cout << "Test Concat_position PASSED" << endl;
}