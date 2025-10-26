#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
	T _value;
	Node* prev;
	Node* next;
};

#endif