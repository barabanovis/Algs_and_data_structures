#ifndef LINKED_LIST_H
#define LINDED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList {
private:
	Node<T>* _head;
	Node<T>* _tail;

	Node<T>* get_head() const;
	Node<T>* get_tail() const;
public:
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
LinkedList<T>::get_head() const{
	return _head;
}

template <typename T>
LinkedList<T>::get_tail() const{
	return _tail;
}

template <typename T>
bool LinkedList<T>::is_empty() const {
	return (!_head)
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

template <typename T>
LinkedList<T>::~LinkedList() {
	if (is_emplty()) return;

	Node<T>* p1=get_head();
	Node<T>* p2 = p1->next;
	
	while (!p2) {
		delete p1;
		p1 = p2;
		p2 = p2->next;
	}
	return;
}

// операции для добавления величины в конец и начало списка
//в конец
template <typename T>
void LinkedList<T>::push_tail(const T& val) {
	Node<T>* new_node = new Node<T>;
	new_node->value = val;
	new_node->next = nullptr;
	new_node->prev = get_tail();
	get_tail()->next = new_node;
	_tail = new_node;
}

//в начало
template <typename T>
void LinkedList<T>::push_head(const T& val) {
	Node<T>* new_node = new Node<T>;
	new_node->value = val;
	new_node->prev = nullptr;
	new_node->next = get_head();
	get_head()->prev = new_node;
	_head = new_node;
}

//операции для склейки списков
//список cpy клеим в начало
template <typename T>
void LinkedList<T>::push_head(const LinkedList<T>& cpy) {

}

//список cpy клеим в конец
#endif