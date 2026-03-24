#ifndef SET_H
#define SET_H

struct Node {
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};


class Set {
private:
	Node* _root;

	Node* tree_copy(Node* root);
	void tree_print(Node* root);
	bool tree_contains(Node* root, int key);
	size_t tree_size(Node* root) const;
	bool tree_isbalanced(Node* root) const;
public:
	Set();
	Set(const Set& copy);


	void print() const;
	bool insert(int key);
	bool contains(int key) const;
	bool erase(int key);

	size_t size() const;
	bool strictly_balanced() const;


};

#endif