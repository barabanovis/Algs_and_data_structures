#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
	T value;
	Node* prev;
	Node* next;
};

#endif