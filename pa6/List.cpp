#include "List.h"

// --- Private constructors ---

List::Node::Node(ListElement val) {
      	data = val;
      	next = nullptr;
  prev = nullptr;
}

// --- Public constructors ---
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

List::List(const List& src) {
      	frontDummy = new Node(0);
      	backDummy = new Node(0);


      	frontDummy->next = backDummy;
       	backDummy->prev = frontDummy;

  
	beforeCursor = frontDummy;
      	afterCursor = backDummy;

      	pos_cursor = 0;
       	num_elements = 0;


      	Node* temp = src.frontDummy->next;
  while (temp != src.backDummy) {
    this->insertBefore(temp->data);
    temp = temp->next;
  }
}

List::~List() {
      	this->clear();
      	delete frontDummy;
      	delete backDummy;
}

int List::length() const {
      	return num_elements;
}

ListElement List::front() const {

      	if (length() <= 0) throw std::length_error("List: front(): empty list");

      	return frontDummy->next->data;
}

ListElement List::back() const {

      	if (length() <= 0) throw std::length_error("List: back(): empty list");

      	return backDummy->prev->data;
}

int List::position() const {

      	return pos_cursor;
}

ListElement List::peekNext() const {
      	if (position() == length()) throw std::range_error("List: peekNext(): cursor at back");
      	if (position() > length()) throw std::range_error("List: peekNext(): cursor at front");

      	return afterCursor->data;
}

ListElement List::peekPrev() const {
      	if (position() == 0) throw std::range_error("List: peekPrev(): cursor at front");

      	if (position() < 0) throw std::range_error("List: peekPrev(): cursor at back");
      	return beforeCursor->data;
}

void List::clear() {
      	moveFront();
      	while (length() > 0) eraseAfter();
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
      	if (position() == length()) throw std::range_error("List: moveNext(): cursor at back");
      	if (position() > length()) throw std::range_error("List: moveNext(): cursor at front");
      	beforeCursor = afterCursor;
      	afterCursor = afterCursor->next;
      	pos_cursor++;
      	return beforeCursor->data;
}

ListElement List::movePrev() {
      	if (position() == 0) throw std::range_error("List: movePrev(): cursor at front");
      	if (position() < 0) throw std::range_error("List: movePrev(): cursor at back");
      	afterCursor = beforeCursor;

      	beforeCursor = beforeCursor->prev;
      	pos_cursor--;
      	return afterCursor->data;
}

void List::insertAfter(ListElement val) {
      	Node* newNode = new Node(val);
      	newNode->prev = beforeCursor;
      	newNode->next = afterCursor;
      	beforeCursor->next = newNode;
      	afterCursor->prev = newNode;
      	afterCursor = newNode;
      	num_elements++;
}

void List::insertBefore(ListElement val) {
      	Node* newNode = new Node(val);
      	newNode->prev = beforeCursor;
      	newNode->next = afterCursor;
      	beforeCursor->next = newNode;
      	afterCursor->prev = newNode;
      	beforeCursor = newNode;
      	pos_cursor++;
      	num_elements++;
}

void List::setAfter(ListElement val) {
      	if (position() == length()) throw std::range_error("List: setAfter(): cursor at back");
      	if (position() > length()) throw std::range_error("List: setAfter(): cursor at front");
      	afterCursor->data = val;
}

void List::setBefore(ListElement val) {
      	if (position() == 0) throw std::range_error("List: setBefore(): cursor at front");
      	if (position() < 0) throw std::range_error("List: setBefore(): cursor at back");
      	beforeCursor->data = val;
}

void List::eraseAfter() {
      	if (position() == length()) throw std::range_error("List: eraseAfter(): cursor at back");
      	if (position() > length()) throw std::range_error("List: eraseAfter(): cursor at front");
      	Node* temp = afterCursor;
      	beforeCursor->next = temp->next;
      	afterCursor->next->prev = beforeCursor;
      	afterCursor = temp->next;
      	delete temp;
      	num_elements--;
}

void List::eraseBefore() {

      	if (position() == 0) throw std::range_error("List: eraseBefore(): cursor at front");
      	if (position() < 0) throw std::range_error("List: eraseBefore(): cursor at back");
      	Node* temp = beforeCursor;
      	afterCursor->prev = temp->prev;
      	afterCursor->prev->next = afterCursor;
      	beforeCursor = temp->prev;
      	delete temp;
      	num_elements--;
      	pos_cursor--;
}

int List::findNext(ListElement val) {
      	while (position() < length()) {
	    	if (peekNext() == val) {
		  	moveNext();
		  	return position();
	    	}
	    	moveNext();
      	}
      	return -1;
}

int List::findPrev(ListElement val) {
      	while (position() > 0) {
	    	if (peekPrev() == val) {
		  	movePrev();
		  	return position();
	    	}
	    	movePrev();
      	}
      	return -1;
}

void List::cleanup() {
      	int currPos = 0;
      	Node* currNode = frontDummy->next;
      	while (currNode != backDummy) {
	    	int cmpPos = currPos + 1;
	    	Node* cmpNode = currNode->next;
	    	while (cmpNode != backDummy) {
		  	Node* prevNode = cmpNode->prev;
		  	if (cmpNode->data == currNode->data) {
				if (cmpNode == beforeCursor) {
			      		eraseBefore();
			      		cmpNode = prevNode;
				} else if (cmpNode == afterCursor) {
			      		eraseAfter();
			      		cmpNode = prevNode;
				} else {
			      		Node* tmp = cmpNode;
			      		cmpNode = cmpNode->prev;
			      		tmp->prev->next = tmp->next;
			      		tmp->next->prev = tmp->prev;
			      		delete tmp;
			      		num_elements--;
			      		if (cmpPos <= position()) pos_cursor--;
				}
		  	}
		  	cmpNode = cmpNode->next;
		  	cmpPos++;
	    	}
	    	currNode = currNode->next;
	    	currPos++;
      	}
}

List List::concat(const List& src) const {
      	List result;
      	for (Node* temp = frontDummy->next; temp != backDummy; temp = temp->next) result.insertBefore(temp->data);
      	for (Node* temp2 = src.frontDummy->next; temp2 != src.backDummy; temp2 = temp2->next) result.insertBefore(temp2->data);
      	result.moveFront();
      	return result;
}

std::string List::to_string() const {
      	std::string s = "(";
      	for (Node* temp = frontDummy->next; temp != backDummy; temp = temp->next) {
	    	s += std::to_string(temp->data) + (temp != backDummy->prev ? ", " : ")");
      	}
      	return s;
}

bool List::equals(const List& other) const {
      	if (length() != other.length()) return false;
      	for (Node* a = frontDummy->next, *b = other.frontDummy->next; a != backDummy; a = a->next, b = b->next) {
	    	if (a->data != b->data) return false;
      	}
      	return true;
}

std::ostream& operator<<(std::ostream& os, const List& lst) {
      	return os << lst.List::to_string();
}

bool operator==(const List& a, const List& b) {
      	return a.List::equals(b);
}

List& List::operator=(const List& src) {
      	if (this != &src) {
	    	List temp = src;
	    	std::swap(frontDummy, temp.frontDummy);
	    	std::swap(backDummy, temp.backDummy);
	    	std::swap(beforeCursor, temp.beforeCursor);
	    	std::swap(afterCursor, temp.afterCursor);
	    	std::swap(pos_cursor, temp.pos_cursor);
	    	std::swap(num_elements, temp.num_elements);
      	}
      	return *this;
}