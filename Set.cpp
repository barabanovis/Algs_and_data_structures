#include <iostream>
#include "Set.h"

using namespace std;

Set::Set() :_root(nullptr) {};


Node* tree_copy(Node* root) {
	if (!root) {
		return nullptr;
	}

	Node* new_node = new Node;
	new_node->value = root->value;

	if (root->left) {
		new_node->left = tree_copy(root->left);
	}
	else {
		new_node->left = nullptr;
	}

	if (root->right) {
		new_node->right = tree_copy(root->right);
	}
	else {
		new_node->right = nullptr;
	}
}

Set::Set(const Set& copy) {
	_root = tree_copy(copy._root);
}

void tree_print(Node* root) {
	if (!root) {
		return;
	}
	tree_print(root->left);
	cout << root->value << " ";
	tree_print(root->right);
}

void Set::print()const {
	tree_print(_root);
}

Node* tree_find(Node* root, int key) {
	Node* ptr = root;
	while (ptr) {
		if (ptr->value == key) {
			return ptr;
		}
		else if (key < ptr->value) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	return nullptr;
}

bool Set::contains(int key) const {
	return tree_find(_root, key);
}

size_t tree_size(Node* root)  {
	if (!root) {
		return 0;
	}
	return tree_size(root->left) + 1 + tree_size(root->right);
}

size_t Set::size() const {
	return tree_size(_root);
}

size_t tree_height(Node* root) {
	if (!root) {
		return 0;
	}
	else {
		return max(tree_height(root->left), tree_height(root->right)) + 1;
	}
}

int vertex_balance_index(Node* root)  {
	if (!root) {
		return 0;
	}
	return (int)tree_height(root->left) - (int)tree_height(root->right);
}

size_t max(size_t a, size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

bool vertex_is_balanced(Node* root) {
	return abs(vertex_balance_index(root)) <= 1;
}

bool tree_is_balanced(Node* root) {
	if (!root) {
		return true;
	}
	return vertex_is_balanced(root)&& tree_is_balanced(root->left) && tree_is_balanced(root->right);
}

bool Set::strictly_balanced() const {
	return tree_is_balanced(_root);
}


// подразумевают автобалансировку

/*
bool Set::erase(int key) {
	Node* ptr = _root;
	Node* prev = ptr;
	while (ptr) {
		if (ptr->value == key) {
			break;
		}
		else if (key < ptr->value) {
			prev = ptr;
			ptr = ptr->left;
		}
		else {
			prev = ptr;
			ptr = ptr->right;
		}
	}
	if (!ptr) {
		return false;
	}

	bool is_delete_left_son = (prev->left == ptr);
	 
	// deleting vertex hasn't got any children
	if (!ptr->left && !ptr->right) {
		if (is_delete_left_son) {
			prev->left = nullptr;
		}
		else {
			prev->right = nullptr;
		}

		delete ptr;
		ptr = nullptr;

		return true;
	}

	// deleting vertex has one son
	if (ptr->left && !ptr->right) {
		if (is_delete_left_son) {
			prev->left = ptr->left;
		}
		else {
			prev->right = ptr->left;
		}
		delete ptr;
		ptr = nullptr;
		return true;
	}

	if (!ptr->left && ptr->right) {
		if (is_delete_left_son) {
			prev->left = ptr->right;
		}
		else {
			prev->right = ptr->right;
		}
		delete ptr;
		ptr = nullptr;
		return true;
	}

	//deleting vertex has son and daugther
	Node* ptr_prime_prev = ptr;
	Node* ptr_prime = ptr->left;
	while (ptr_prime->right) {
		ptr_prime_prev = ptr_prime;
		ptr_prime = ptr_prime->right;
	}
	ptr->value = ptr_prime->value;
	// delete ptr_prime
	if (ptr_prime_prev->left == ptr) {
		ptr_prime_prev->left = ptr_prime->left;
	}
	else {
		ptr_prime_prev->right = ptr_prime->left;
	}
	delete ptr_prime;
	ptr_prime = nullptr;
	return true;
}
*/

/*
bool Set::insert(int key) {
	if (!_root) {
		Node* new_node = new Node;
		new_node->value = key;
		new_node->left = nullptr;
		new_node->right = nullptr;
		_root = new_node;
		return true;
	}


	Node* ptr_prev = _root;
	Node* ptr = _root;
	while (ptr) {
		ptr_prev = ptr;
		if (ptr->value == key) {
			return false;
		}
		else if (ptr->value < key) {
			ptr = ptr->right;
		}
		else {
			ptr = ptr->left;
		}
	}
	Node* new_node = new Node;
	new_node->value = key;
	new_node->left = nullptr;
	new_node->right = nullptr;
	if (key < ptr_prev->value) {
		ptr_prev->left = new_node;
	}
	else {
		ptr_prev->right = new_node;
	}
	return true;
}
*/

Node* small_right_rotation(Node* root) {
	Node* a = root;
	Node* b = root->left;
	Node* R_b = b->right;

	root = b;
	b->right = a;
	a->left = R_b;
	return root;
}

Node* small_left_rotation(Node* root) {
	Node* a = root;
	Node* b = root->right;
	Node* L_b = b->left;

	root = b;
	b->left = a;
	a->right = L_b;
	return root;
}

Node* big_left_rotation(Node* root) {
	Node* a = root;
	Node* b = a->right;
	Node* c = b->left;

	c = small_right_rotation(b);
	c = small_left_rotation(a);
	return c;
}

Node* big_right_rotation(Node* root) {
	Node* a = root;
	Node* b = a->left;
	Node* c = b->right;

	c = small_left_rotation(b);
	c = small_right_rotation(a);
	return c;
}


void balance(Node*& root) {
	int da = vertex_balance_index(root);
	int db = vertex_balance_index(root->right);

	if (da == -2 && (db == 0 || db == -1)) {
		root = small_left_rotation(root);
	}
	else if (db == 2 && (da == 0 || da == -1)) {
		root = small_right_rotation(root);
	}
	else if (da == -2 && db==1) {
		root = big_left_rotation(root);
	}
	else if (db == -2 && da == 1) {
		root = big_right_rotation(root);
	}

	da = vertex_balance_index(root);
	db = vertex_balance_index(root->left);

	if (da == -2 && (db == 0 || db == -1)) {
		root = small_left_rotation(root);
	}
	else if (db == 2 && (da == 0 || da == -1)) {
		root = small_right_rotation(root);
	}
	else if (da == -2 && db == 1) {
		root = big_left_rotation(root);
	}
	else if (db == -2 && da == 1) {
		root = big_right_rotation(root);
	}
}

bool insert_tree(Node*& root, int key) {
	if (!root) {
		Node* new_node = new Node;
		new_node->value = key;
		new_node->left = nullptr;
		new_node->right = nullptr;
		root = new_node;
		return true;
	}


	if (root->value == key) {
		return false;
	}

	bool inserted = false;
	if (key < root->value) {
		inserted = insert_tree(root->left,key);
	}
	else if (key > root->value) {
		inserted = insert_tree(root->right, key);
	}
	
	if (inserted && !vertex_is_balanced(root)) {
		balance(root);
	}
	return inserted;
}

bool erase_tree(Node*& root, int key) {
	if (!root) {
		return false;
	}
	
	if (root->value == key) {
		delete root;
		root = nullptr;
		return true;
	}

	bool erased = false;

	if (key < root->value) {
		erased = erase_tree(root->left, key);
	}
	else if (key > root->value) {
		erased = erase_tree(root->right, key);
	}


	if (erased) {
		balance(root);
	}
	return erased;
}

bool Set::insert(int key) {
	return insert_tree(_root, key);
}

bool Set::erase(int key) {
	return erase_tree(_root, key);
}

vector<int> tree_to_vector(Node* root) {
	vector<int> v1(0);
	if (!root) {
		return v1;
	}

	v1 = tree_to_vector(root->left);
	v1.push_back(root->value);
	vector<int> v2 = tree_to_vector(root->right);

	v1.insert(v1.end(), v2.begin(), v2.end());
	return v1;
}

vector<int> Set::to_vector()const {
	return tree_to_vector(_root);
}