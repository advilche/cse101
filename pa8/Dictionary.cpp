/*
 *
 */

#include <iostream>
#include <string>
#include "Dictionary.h"

#define BLACK 0
#define RED 1

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
	parent	= nullptr;
	left 	= nullptr;
	key	= k;
	val	= v;

	color = BLACK;
}

Dictionary::Dictionary() { 
	nil = new Node(" ", -1);
	
	num_pairs 	= 0;
	current 	= nil;
	root 		= nil;
}

Dictionary::Dictionary(const Dictionary& D) {
      	nil = new Node(" ", -1);
      
	num_pairs 	= 0;
	current 	= nil;
	root 		= nil;
	preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
       	clear();
      	delete nil; 
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
void Dictionary::inOrderString(std::string& s, Node* R) const {
      	if (R != nil){
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + '\n';
		inOrderString(s, R->right);
	} else{
		return;
	}
}

// preOrderString()

void Dictionary::preOrderString(std::string& s, Node* R) const {
      	if (R != nil){
	      	s += R->key + '\n';
	      	preOrderString(s, R->left);
		preOrderString(s, R->right);
	} else {
		return;
	}
}
// preOrderCopy()
void Dictionary::preOrderCopy(Node* R, Node* N) {
      	if (R != N){ 
		setValue(R->key, R->val);
	      	preOrderCopy(R->left, N);
	      	preOrderCopy(R->right, N);
	} else {
		return;
	}
}

// postOrderDelete()  
void Dictionary::postOrderDelete(Node* R) {
      	if (R != nil) {
		postOrderDelete(R->left);
		postOrderDelete(R->right);
	      	delete(R);
	} else {
		return;
	}
}

// search() 

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
      	if (R != nil){
	      	if (R->key > k) {
		    	return search(R->left, k);
	      	} else if (R->key < k) return search(R->right, k);
	      	return R;
	} else {
		return R;
	}
}

// findMin()
Dictionary::Node* Dictionary::findMin(Node* R) {
      	if (R == nil){
	       	return nil;
	}
      	
	Node *r = R;
      	while (r->left != nil) {
	    	r = r->left;
      	}
      	return r;
}

// findMax()

Dictionary::Node* Dictionary::findMax(Node* R) {

      	if (R == nil) return nil;
  Node *temp = R;
  while (temp->right != nil) {
    temp = temp->right;
  }
  return temp;
}

// findNext()
//
Dictionary::Node* Dictionary::findNext(Node* N) {
  //if (N == nil) return nil;
  if (N->right != nil) return findMin(N->right);
  Node *temp = N->parent;
  while (temp != nil && N == temp->right) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// findPrev() 

Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N != nil){
		if (N->left != nil) {
			return findMax(N->left);
		}
		Node *n = N->parent;
		while (n != nil && N == n->left){
			N = n;
			n = n->parent;
		}
		return n;
	}
	return nil;
}

/*
Direi:e*  )n -!  xfNe-timi p) m  p
  }
  return temp;
}*/

// Access functions --------------------------------------------------------

// size() 
int Dictionary::size() const {
  return num_pairs;
}

// contains() 
bool Dictionary::contains(keyType k) const {
  return this->search(root, k) != nil;
}

// getValue() 

valType& Dictionary::getValue(keyType k) const {
	Node *n = this->search(root, k);
	if (n != nil){
		return n->val;
	} else {
		 throw std::logic_error("In Dictionary ADT: Function getValue(): the key does not exist");
	}
}

// hasCurrent() 
bool Dictionary::hasCurrent() const {
  return current != nil;
}

// currentKey()
keyType Dictionary::currentKey() const {
      	if (current != nil){
		return current->key;
	} else {
	       	throw std::logic_error("In Dictionary ADT: Function currentKey(): current is not defined");
	}
}

// currentVal() 
valType& Dictionary::currentVal() const {
      	if (current != nil){
		return current->val;
	} else {
		throw std::logic_error("In Dictionary ADT: Function currentVal(): current is not defined");
	}
}

// Manipulation procedures -------------------------------------------------

// clear() resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
      	postOrderDelete(root); // starting from the left
      	root = nil;
      	current = nil;
	//just resetting to the nil state
      	num_pairs = 0;
}

// setValue()

void Dictionary::setValue(keyType k, valType value) {
      	Node* N = new Node(k, value);
      	N->color = RED; // New nodes are red
      	N->left = nil;
      	N->right = nil;

      	Node* parent = nil;
      	Node* current = root;

      	// Perform BST insert
      	while (current != nil) {
	    	parent = current;
	    	if (k < current->key) {
		  	current = current->left;
	    	} else if (k > current->key) {
		  	current = current->right;
	    	} else {      // Key exists, update val
		  	current->val = value;
		  	delete N;
		  	return;
	    	}
      	}

      	N->parent = parent;
      	if (parent == nil) {
	    	root = N; // Tree was empty, new node becomes the root
      	} else if (k < parent->key) {
	    	parent->left = N;
      	} else {
	    	parent->right = N;
      	}

      	num_pairs++; // increment
      	// restore RB
      	RB_InsertFixUp(N);
}


/*
if a pair withstelosw)ia v e-; ode* parent = this->nil;
  Not-it- u r pree r pri  t;tr}pel  INdn
}*/

//remove()
void Dictionary::remove(keyType k) {
      	if (!contains(k)) {
		throw std::logic_error("In Dictionary ADT: Function remove(): the key currently is nonexistent");
	}
	if (current->key == k) {
		current = nil;
	}
	
      	RB_Delete(search(root, k));
      	num_pairs--;
}

// begin() 
void Dictionary::begin() {
      	if (!(num_pairs > 0)){
	       	throw std::length_error("In Dictionary ADT: Function begin(): Dictionary is currently empty");}
      	current = findMin(root);
}

// end() 
//
void Dictionary::end() {
      	if (!(num_pairs > 0)){
      		throw std::length_error("In Dictionary ADT: Function end(): Dictionary is currently empty");
      	}
      	current = findMax(root);
}

// next() 
void Dictionary::next() {
  if (current != nil) {
	  current = findNext(current);
  } else {
	  throw std::logic_error("In Dictionary ADT: Function next(): current not defined");
  }
}

// prev() 
void Dictionary::prev() {
  if (current != nil){
	  current = findPrev(current);
  } else {
	  throw std::logic_error("In Dictionary ADT: Function prev(): current not defined");
  }
}

// Below are PA8 functions
// RBT Helper Functions (Optional) -----------------------------------------

void Dictionary::LeftRotate(Node* N) {
    	Node* rightChild = N->right;               // Get N's right child
    	Node* leftGrandchild = rightChild->left;   // Get the left child of rightChild

    	if (N->parent == nil) {
		root = rightChild;
    	} else if (N == N->parent->left) {
		N->parent->left = rightChild;
    	} else {
		N->parent->right = rightChild;
    	}

    	rightChild->parent = N->parent;            // Update rightChild's parent to N's parent
    	N->parent = rightChild;                    // Update N's parent to rightChild

    	N->right = leftGrandchild;                 // Make leftGrandchild the new right child of N
    	if (leftGrandchild != nil) {
		leftGrandchild->parent = N;
    	}

    	rightChild->left = N;                      // Make N the left child of rightChild
}

void Dictionary::RightRotate(Node* N) {
    	Node* leftChild = N->left;               // Get N's left child
    	Node* rightGrandchild = leftChild->right; // Get the right child of leftChild

    	if (N->parent == nil) {
		root = leftChild;
    	} else if (N == N->parent->left) {
		N->parent->left = leftChild;
    	} else {
		N->parent->right = leftChild;
    	}

    	leftChild->parent = N->parent;           // Update leftChild's parent to N's parent
    	N->parent = leftChild;                   // Update N's parent to leftChild

    	N->left = rightGrandchild;               
    	if (rightGrandchild != nil) {
    		rightGrandchild->parent = N;
    	}
    leftChild->right = N;                    
}

/*
void Dictionary::RightRotate(Node* N) {
    	Nod Get N's left og g e oC P o t'p p = sn li }*/

/*
void Dictionary::RightRotate(Node* N) {
  Nodieea - -NfG;
  leftChild->parent = N->par t{ ls=t{ahhe -e af tdrce
*/

void Dictionary::RB_InsertFixUp(Node* N) {
      	while (N->parent->color == RED) { // Case: Parent is RED
	    	Node* grandparent = N->parent->parent;

	    	if (N->parent == grandparent->left) { // Parent is left
		  	Node* uncle = grandparent->right;

		  	if (uncle->color == RED) { 
				// Case 1: Uncle is RED

				N->parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				N = grandparent; // Move up 
		  	} else {
				if (N == N->parent->right) { 
			      		// Case 2: Uncle is BLACK N is right

			      		N = N->parent;
			      		LeftRotate(N); //  make N a left
				}
				// Case 3: Uncle is BLACK n is left
				N->parent->color = BLACK;
				grandparent->color = RED;
				RightRotate(grandparent); // Fix gp level
		  	}
			
	    	} else { // Parent is a right child
		  	Node* uncle = grandparent->left;

		  	if (uncle->color == RED) { 
				// Case 4: Uncle is RED

				N->parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				N = grandparent; // Move up 
		  	} else {
				if (N == N->parent->left) { 
			      		// Case 5: Uncle is BLACK n left

			      		N = N->parent;
			      		RightRotate(N); // Rotate to make N right
				}
				// Case 6: Uncle is BLACK n is right

				N->parent->color = BLACK;
				grandparent->color = RED;
				LeftRotate(grandparent); // Fix at gp level
		  	}
	    	}
      	}
      	root->color = BLACK; 
}


/*
void Dictionary::RB_InsertFixUp(Node* N) {
  whil-D* >i n crc  >eAgc        N = grandparent;
      } else if (N == N->parent->right) {
        N = N->parent;
 o  eB -;hd sdre r eu= nE ts-tN;h {p  eRLa  o
}*/

void Dictionary::RB_Transplant(Node* u, Node* v) {
    	if (u->parent == nil) {
		root = v;
    	} else if (u == u->parent->left) {
		u->parent->left = v;
    	} else {
		u->parent->right = v;
    	}
    	v->parent = u->parent;
}


void Dictionary::RB_DeleteFixUp(Node* N) {
    	while (N != root && N->color == BLACK) {
		if (N == N->parent->left) {
	    		Node* sibling = N->parent->right;
            
            // Case 1: Sibling is RED

	    		if (sibling->color == RED) {
				sibling->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				sibling = N->parent->right;
	    		}

            // Case 2: Both sibling's children are BLACK

	    		if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
				sibling->color = RED;
				N = N->parent;
	    		} else {
                // Case 3: Sibling's right child is BLACK

				if (sibling->right->color == BLACK) {
		    			sibling->left->color = BLACK;
		    			sibling->color = RED;
		    			RightRotate(sibling);
		    			sibling = N->parent->right;
				}

                // Case 4: Sibling's right child is RED

				sibling->color = N->parent->color;
				N->parent->color = BLACK;
				sibling->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
	    		}
		} else {
	    		Node* sibling = N->parent->left;

            // Case 1: Sibling is RED

	    		if (sibling->color == RED) {
				sibling->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				sibling = N->parent->left;
	    		}

            // Case 2: Both sibling's children are BLACK

	    		if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
				sibling->color = RED;
				N = N->parent;
	    		} else {
                // Case 3: Sibling's left child is BLACK

				if (sibling->left->color == BLACK) {
		    			sibling->right->color = BLACK;
		    			sibling->color = RED;
		    			LeftRotate(sibling);
		    			sibling = N->parent->left;
				}

                // Case 4: Sibling's left child is RED

				sibling->color = N->parent->color;
				N->parent->color = BLACK;
				sibling->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
	    		}
		}  
	}
	N->color = BLACK;
}


void Dictionary::RB_Delete(Node* N) {
    	Node* node = N;
    	Node* temp;
    	int node_color = node->color;

    	if (node->left == nil) {
        // Case 1: Node has no left child

		temp = node->right;
		RB_Transplant(node, node->right);
    	} else if (node->right == nil) {
        // Case 2: Node has no right child

		temp = node->left;
		RB_Transplant(node, node->left);
    	} else {
        // Case 3: Node has two children

		Node* successor = findMin(node->right);
		node_color = successor->color;
		temp = successor->right;

		if (successor->parent == node) {
	    		temp->parent = successor; // Successor is directly under the node being deleted

		} else {
	    		RB_Transplant(successor, successor->right);
	    		successor->right = node->right;
	    		successor->right->parent = successor;
		}

		RB_Transplant(node, successor);
		successor->left = node->left;
		successor->left->parent = successor;
		successor->color = node->color;
    	}

    	if (node_color == BLACK) {
        // 
		RB_DeleteFixUp(temp);
    	}
	
    	delete node;
}


std::string Dictionary::to_string() const {
      	std::string s = "";
      	inOrderString(s, root);
      	return s;
}

// pre_string()
std::string Dictionary::pre_string() const {
      	std::string s = "";
      	preOrderString(s, root);
      	return s;
}

// equals()
bool Dictionary::equals(const Dictionary& D) const {
      	return (num_pairs == D.num_pairs) && (to_string() == D.to_string());
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
      	return stream << D.to_string();
}

// operator==()
//
bool operator==( const Dictionary& A, const Dictionary& B ) {
      	return A.equals(B);
}


// operator=()
Dictionary& Dictionary::operator=( const Dictionary& D ) {
      	if (this != &D) {
	    	Dictionary temp = D;
	    	std::swap(nil, temp.nil);
	    	std::swap(root, temp.root);
	    	std::swap(current, temp.current);
	    	std::swap(num_pairs, temp.num_pairs);
      	}
      	return *this;
}