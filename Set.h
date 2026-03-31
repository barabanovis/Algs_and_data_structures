#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>

struct Node {
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};


class Set {
private:
	Node* _root;
public:
	Set();
	Set(const Set& copy);

	void print() const;
	bool insert(int key);
	bool contains(int key) const;
	bool erase(int key);

	size_t size() const;
	bool strictly_balanced() const;

	std::vector<int> to_vector() const;
};

#endif