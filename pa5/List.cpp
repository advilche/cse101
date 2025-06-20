#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "List.h"

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertAfter(N->data);
        moveNext();
        N = N->next;
    }
}

List::~List() {
    moveBack();
    while (num_elements > 0) {
        eraseBefore();
    }
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (length() == 0) {
        throw std::length_error("List: front(): empty List");
    }
    return (frontDummy->next->data);
}

ListElement List::back() const {
    if (length() == 0) {
        throw std::length_error("List: back(): empty List");
    }
    return (backDummy->prev->data);
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (!(position() < length())) {
        throw std::domain_error("List: peekNext(): cursor at end of List");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (!(position() > 0)) {
        throw std::domain_error("List: peekPrev(): cursor at beginning of List");
    }
    return beforeCursor->data;
}

void List::clear() {
    moveBack();
    while (num_elements > 0) {
        eraseBefore();
    }
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
}

ListElement List::moveNext() {
    if (!(position() < length())) {
        throw std::domain_error("List: moveNext(): cursor at end of List");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor += 1;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (!(position() > 0)) {
        throw std::domain_error("List: movePrev(): cursor at beginning of List");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor -= 1;
    return afterCursor->data;
}

void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    pos_cursor++;
    num_elements++;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    afterCursor = newNode;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::domain_error("List: setAfter(): cursor is at end of List");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::domain_error("List: setBefore(): cursor is at beginning of List");
    }
    beforeCursor->data = x;
}

void List::eraseAfter() {
    if (!(position() < length())) {
        throw std::domain_error("List: eraseAfter(): cursor is at or beyond the last element");
    }
    Node* temp = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    delete temp;
    num_elements -= 1;
}

void List::eraseBefore() {
    if (position() == 0) {
        throw std::domain_error("List: eraseBefore(): cursor is at beginning of List");
    }
    Node* temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete temp;
    num_elements -= 1;
    pos_cursor -= 1;
}

int List::findNext(ListElement x) {
    while (pos_cursor < length()) {
        if (peekNext() == x) {
            moveNext();
            return pos_cursor;
        } else {
            moveNext();
        }
    }
    moveBack();
    return -1;
}

int List::findPrev(ListElement x) {
    while (pos_cursor > 0) {
        if (peekPrev() == x) {
            movePrev();
            return pos_cursor;
        } else {
            movePrev();
        }
    }
    moveFront();
    return -1;
}

void List::cleanup() {
    if (num_elements <= 1) return;
    std::unordered_set<ListElement> uniqueElements;
    Node* currentNode = frontDummy->next;
    Node* nextNode;
    int originalCursorPosition = pos_cursor;
    int updatedCursorPosition = 0;
    while (currentNode != backDummy) {
        nextNode = currentNode->next;
        if (uniqueElements.count(currentNode->data)) {
            currentNode->prev->next = currentNode->next;
            currentNode->next->prev = currentNode->prev;
            if (currentNode == beforeCursor) {
                beforeCursor = currentNode->prev;
            }
            if (currentNode == afterCursor) {
                afterCursor = currentNode->next;
            }
            delete currentNode;
            num_elements--;
            if (updatedCursorPosition < originalCursorPosition) {
                originalCursorPosition--;
            }
        } else {
            uniqueElements.insert(currentNode->data);
            updatedCursorPosition++;
        }
        currentNode = nextNode;
    }
    pos_cursor = originalCursorPosition;
}

List List::concat(const List& L) const {
    List N;
    Node* current = this->frontDummy->next;
    while (current != this->backDummy) {
        N.insertAfter(current->data);
        current = current->next;
    }
    current = L.frontDummy->next;
    while (current != L.backDummy) {
        N.insertAfter(current->data);
        current = current->next;
    }
    N.moveFront();
    return N;
}

std::string List::to_string() const {
    std::stringstream ss;
    ss << "(";
    Node* current = frontDummy->next;
    bool first = true;
    while (current != backDummy) {
        if (!first) {
            ss << ", ";
        }
        ss << current->data;
        first = false;
        current = current->next;
    }
    ss << ")";
    return ss.str();
}

bool List::equals(const List& R) const {
    if (R.length() != this->length()) {
        return false;
    }
    Node* current = this->frontDummy->next;
    Node* currentR = R.frontDummy->next;
    while (current != backDummy) {
        if (current->data != currentR->data) {
            return false;
        } else {
            current = current->next;
            currentR = currentR->next;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
    stream << L.to_string();
    return stream;
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}

