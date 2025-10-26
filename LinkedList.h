#ifndef LINKED_LIST_H
#define LINDED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList {
private:
	Node<T>* _head;

public:
	Node<T>* get_head() const;
	bool is_empty() const;

	LinkedList();
	LinkedList(const LinkedList<T>& cpy);
	LinkedList(const int a, const int b);

	~LinkedList();

	T operator=(const T& rhs);

	void push_tail(const T& elem);
	void push_tail(const LinkedList<T>& list);
	
	void push_head(const T& elem);
	void push_head(const LinkedList<T>% list);

	T pop_head();
	T pop_tail();

	void delete_node(const T& val); 

	const T operator[](const int ind) const;
	T& operator[](const int ind);
};

template <typename T>
LinkedList<T>::get_head() {
	return _head;
}


template <typename T>
LinkedList<T>::LinkedList() {
	_head = nullptr;
}

template <typename T>
bool LinkedList<T>::is_empty() {
	return (!_head);
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& cpy) {
	if (cpy.is_empty()) {
		this = new LinkedList();
		return;
	}
	Node<T>* cpy_cur = cpy.get_head();
	
}

#endif