#include "Dictionary.h"
//

// Class Constructors & Destructors
Dictionary::Node::Node(keyType k, valType v) {
      	key 	= k;
      	val 	= v;
      	parent 	= nullptr;
      	left 	= nullptr;
      	right 	= nullptr;
}

Dictionary::Dictionary() {
      	nil 	  = nullptr;
      	current   = nullptr;
      	root 	  = nullptr;
      	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
      	nil	  = new Node(" ", -1);
      	current   = nil;
      	root   	  = nil;
      	num_pairs = 0;

      	preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
      	clear();

      	delete nil;
}

// Helper Functions
void Dictionary::inOrderString(std::string& result, Node* subtreeRoot) const {
      	if (subtreeRoot == nil) {
		return;
	}

      	inOrderString(result, subtreeRoot->left);
      	result += subtreeRoot->key + " : " + std::to_string(subtreeRoot->val) + '\n';
      	inOrderString(result, subtreeRoot->right);
}

void Dictionary::preOrderString(std::string& result, Node* subtreeRoot) const {
      	if (subtreeRoot == nil){
	       	return;
	}

      	result += subtreeRoot->key + '\n';
      	
	preOrderString(result, subtreeRoot->left);
      	preOrderString(result, subtreeRoot->right);
}

void Dictionary::preOrderCopy(Node* subtreeRoot, Node* sentinel) {
      	if (subtreeRoot == sentinel){
      		return;
      	}
  
      	setValue(subtreeRoot->key, subtreeRoot->val);
      	
	preOrderCopy(subtreeRoot->left, sentinel);
      	preOrderCopy(subtreeRoot->right, sentinel);
}

void Dictionary::postOrderDelete(Node* subtreeRoot) {
      	if (subtreeRoot == nil){
	       	return;
	}

      	postOrderDelete(subtreeRoot->left);
      	postOrderDelete(subtreeRoot->right);

	delete subtreeRoot;
}

Dictionary::Node* Dictionary::search(Node* subtreeRoot, keyType key) const {
      	if (subtreeRoot == nil) {
		return subtreeRoot; //first
	}

      	if (key < subtreeRoot->key){ //go down left
	       	return search(subtreeRoot->left, key);
	}

	if (key > subtreeRoot->key) { // go down right
		return search(subtreeRoot->right, key);
	}

      	return subtreeRoot; // r
}

Dictionary::Node* Dictionary::findMin(Node* subtreeRoot) {
  if (subtreeRoot == nil) {
	  return nil; // if em
  }

  Node* cNode = subtreeRoot; // cNode, current Node
  
  while (cNode->left != nil) {
    cNode = cNode->left; // the leftmost node is the least
  }
  
  return cNode;
}

Dictionary::Node* Dictionary::findMax(Node* subtreeRoot) {
  if (subtreeRoot == nil) {
	  return nil;
  }
 
  Node* cNode = subtreeRoot; //again

  while (cNode->right != nil) { // the rightmost node is the most
    cNode = cNode->right;
  }

  return cNode;
}

Dictionary::Node* Dictionary::findNext(Node* node) {
      	if (node->right != nil){
	       	return findMin(node->right);
	}
	
	Node* older = node->parent;
      
	while (older != nil && node == older->right) { // for right
	    	node = older;
	    	older = older->parent; //go further up and right
      	}
      	return older;
}

Dictionary::Node* Dictionary::findPrev(Node* node) {
      	if (node == nil) {
		return nil;
	}
	

	if (node->left != nil) {
		return findMax(node->left);
	}

	Node* older = node->parent;

	while (older != nil && node == older->left) { // going up and left
	    	node = older;
	    	older = older->parent;
      	}
      	return older;
}

// Access Functions

int Dictionary::size() const {
      	return num_pairs; // num_pairs is just number of entries in dictionary
}

bool Dictionary::contains(keyType key) const {
      	return search(root, key) != nil; // return whether it contains it or not
}

valType& Dictionary::getValue(keyType key) const {
      	Node* findNode = search(root, key);

      	if (findNode == nil){
	       	throw std::logic_error("In Dictionary ADT: Function getValue(): key object does is non-existent");
	}      

	return findNode->val;
}

bool Dictionary::hasCurrent() const {
      	return current != nil; // return if 
}

keyType Dictionary::currentKey() const {
      	if (current == nil){
	       	throw std::logic_error("In Dictionary ADT: Function currentKey(): current is not defined");
	}
	//
      	return current->key;//
}

/*
valType& Dictionary::currentVal() const {  
        if (current == nil) {
                throw std::logic_error("In Dictionary ADT: Function currentVal(): current is not defined");
        }
        return current->val;
}*/

valType& Dictionary::currentVal() const {
      	if (current == nil) {
		throw std::logic_error("In Dictionary ADT: Function currentVal(): current is not defined");
	}

	return current->val;
}

// Manipulation Procedures
void Dictionary::clear() {
      	postOrderDelete(root);
	//deleting all

      	root 	  = nil;
      	current   = nil;
      	num_pairs = 0;
}

void Dictionary::setValue(keyType key, valType value) {
      	Node* _new 	= new Node(key, value);
      	_new->left 	= nil;
      	_new->right 	= nil;

      	Node* parent	= nil; // where the this pointer w go second v.
      	Node** pointer  = &root;

      	while (*pointer != nil) {
	    	parent = *pointer;
	    	
		if (key < (*pointer)->key) {
		  	pointer = &((*pointer)->left);
	    	} else if (key > (*pointer)->key) {
		  	pointer = &((*pointer)->right);
	    	} else {
		  	(*pointer)->val = value;
		  	delete _new;
		  	return;
	    	}
      	}

      	_new->parent 	= parent;
      	*pointer	= _new;
      	num_pairs++;
}

void Dictionary::remove(keyType key) {
    	if (!contains(key)) {
		throw std::logic_error("In Dictionary ADT: Function remove(): key is non-existent");
    	}


    	Node* nodeToRemove = search(root, key);

	if (nodeToRemove->left == nil || nodeToRemove->right == nil) {
		Node* replacementChild = (nodeToRemove->left == nil) ? nodeToRemove->right : nodeToRemove->left;
		if (nodeToRemove->parent == nil) {      
	    		root = replacementChild;    
		} else if (nodeToRemove == nodeToRemove->parent->left) {      
	    		nodeToRemove->parent->left = replacementChild;    
		} else {      
	    		nodeToRemove->parent->right = replacementChild;    
		}    
		if (replacementChild != nil) replacementChild->parent = nodeToRemove->parent;  
    	} else {    
		Node* inOrderSuccessor = findMin(nodeToRemove->right);    

		if (inOrderSuccessor->parent != nodeToRemove) {      
	    		if (inOrderSuccessor->right != nil) inOrderSuccessor->right->parent = inOrderSuccessor->parent;      
	    		inOrderSuccessor->parent->left = inOrderSuccessor->right;      
	    		inOrderSuccessor->right = nodeToRemove->right;      
	    		inOrderSuccessor->right->parent = inOrderSuccessor;    
		}    
		if (nodeToRemove == root) {
	    		root = inOrderSuccessor;    
		} else if (nodeToRemove == nodeToRemove->parent->left) {      
	    		nodeToRemove->parent->left = inOrderSuccessor;    
		} else {      
	    		nodeToRemove->parent->right = inOrderSuccessor;    

		}    

		inOrderSuccessor->parent = nodeToRemove->parent;    
		inOrderSuccessor->left = nodeToRemove->left;    
		inOrderSuccessor->left->parent = inOrderSuccessor;  
    	}
	
    	if (current == nodeToRemove){
	       	current = nil;
	}

    	delete nodeToRemove;
    	num_pairs--;
}


/*
void Dictionary::remove(keyType key) {
      	if (!contains(key)) {
		throw std::logic_error("In Dictionary ADT: Function remove(): key is non-existent");
	}
}
*/

//

void Dictionary::begin() {
      	if (num_pairs <= 0) {
		throw std::length_error("In Dictionary ADT: Function begin(): Dictionary is empty");
	}

	current = findMin(root);
}

void Dictionary::end() {
      	if (num_pairs <= 0) {
		throw std::length_error("In Dictionary ADT: Function end(): Dictionary is empty");
	}

	current = findMax(root);
}

void Dictionary::next() {
      	if (current == nil){
	       	throw std::logic_error("In Dictionary ADT: Function next(): current is not defined");
	}

	current = findNext(current);
}

void Dictionary::prev() {
      	if (current == nil){
	       	throw std::logic_error("In Dictionary ADT: Function prev(): current is not defined");
	}

      	current = findPrev(current);
}

// Other Functions
std::string Dictionary::to_string() const {
      	std::string result = "";
      	inOrderString(result, root);
      
	return result;
}

std::string Dictionary::pre_string() const {
      	std::string result = "";
      	preOrderString(result, root);

      	return result;
}

bool Dictionary::equals(const Dictionary& D) const {
      	return (num_pairs == D.num_pairs) && (to_string() == D.to_string());
	//
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
      	return stream << D.to_string();
	//
}

bool operator==(const Dictionary& A, const Dictionary& B) {
      	return A.equals(B); //
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
      	if (this != &D) { //swap changes
	    	Dictionary temp = D;
	    	std::swap(nil, temp.nil);
	    	std::swap(root, temp.root);
	    	std::swap(current, temp.current);
	    	std::swap(num_pairs, temp.num_pairs);
      	}
      	return *this;
}