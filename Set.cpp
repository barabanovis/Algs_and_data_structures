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

bool Set::tree_contains(Node* root, int key){
	Node* ptr = root;
	while (ptr) {
		if (ptr->value == key) {
			return true;
		}
		else if (ptr->left < key) {
			return tree_contains(root->left, key);
		}
		else {
			return tree_contains(root->right, key);
		}
	}
	return false;
}

bool Set::contains(int key) const {
	return tree_contains(_root, key);
}

size_t Set::tree_size(Node* root) const {
	if (!root) {
		return 0;
	}
	return tree_size(root->left) + 1 + tree_size(root->right);
}

size_t Set::size() const {
	return tree_size(_root);
}

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
}

