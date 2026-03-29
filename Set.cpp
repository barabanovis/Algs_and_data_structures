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
	_root=tree_copy(copy._root)
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
		if (ptr->key == key) {
			return ptr;
		}
		else if (key < ptr->key) {
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
	return (int)tree_height(root->left) - (int)tree_height(root->right);
}

size_t max(size_t a, size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

int abs(int a) {
	if (a > 0) {
		return a;
	}
	else {
		return -a;
	}
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

bool Set::erase(int key) {
	Node* ptr = _root;
	Node* prev = ptr;
	while (ptr) {
		if (ptr->key == key) {
			break;
		}
		else if (key < ptr->key) {
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

	
}


