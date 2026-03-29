#include "Set.h"

using namespace std;

Set::Set() :_root(nullptr) {};


static Node* Set::tree_copy(Node* root) {
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
	_root=tree_copy(copy._root)
}


void Set::tree_print(Node* root) {
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



bool Set::contains(int key) const {
	Node* ptr = _root;
	while (ptr) {
		if (ptr->key == key) {
			return true;
		}
		else if (key < ptr->key) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	return false;
}

<<<<<<< HEAD
size_t Set::tree_size(Node* root) {
=======
bool Set::contains(int key) const {
	return tree_contains(_root, key);
}

size_t Set::tree_size(Node* root) const {
>>>>>>> 4ef7c47d41c889f3ac88e7eccf4ac007ddefb843
	if (!root) {
		return 0;
	}
	return tree_size(root->left) + 1 + tree_size(root->right);
}

size_t Set::size() const {
	return tree_size(_root);
}

<<<<<<< HEAD
int Set::tree_balance_index(Node* root){}


size_t max(size_t a, size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

size_t Set::tree_height(Node* root) {
	if (!root) {
		return 0;
	}
	else {
		return max(tree_height(root->left), tree_height(root->right)) + 1;
	}
=======
bool Set::tree_isbalanced(Node* root) const{
	if (tree_isbalanced(root->left) && tree_isbalanced(root->right)) {
		int ind = tree_size(root->left) - tree_size(root->right);
		if (ind >= -1 && ind <= 1) {
			return true;
		}
		return false;
	}
	return false;
}

bool Set::strictly_balanced()const {
	return tree_isbalanced(_root);
>>>>>>> 4ef7c47d41c889f3ac88e7eccf4ac007ddefb843
}

