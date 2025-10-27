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

	// онструктор - генератор случайного списка
	//LinkedList(const int a, const int b, const int n); 

	~LinkedList();

	LinkedList<T> operator=(const LinkedList<T>& rhs);

	void push_head(const T& elem);
	void push_head(const LinkedList<T>& list);

	void push_tail(const T& elem);
	void push_tail(const LinkedList<T>& list);

	T pop_head();
	T pop_tail();

	void delete_node(const T& val); 

	const T operator[](const int ind) const;
	T& operator[](const int ind);
};

template <typename T>
Node<T>* LinkedList<T>::get_head() const{
	return _head;
}

template <typename T>
Node<T>* LinkedList<T>::get_tail() const{
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
bool LinkedList<T>::is_empty() const{
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

template <typename T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	// «ачистка данного списка
	if (get_head()) {
		Node<T>* prev = get_head();
		Node<T>* cur = get_head()->next;
		while (cur) {
			delete prev;
			prev = nullptr;
			prev = cur;
			cur = cur->next;
		}
	}
	_head = nullptr;

	//  опирование правого в левый
	Node<T>* p_rhs = rhs->get_head();
	
	if (p_rhs) {
		_head = new Node<T>;
		_head->value = p_rhs->value;
		_head->prev = nullptr;
		p_rhs = p_rhs->next;

		Node<T>* p_cur = _head;
		while (p_rhs) {
			Node<T>* p_new = new Node<T>;
			p_new->value = p_rhs->value;
			p_new->prev = p_cur;
			p_new->next = nullptr;
			p_cur->next = p_new;

			p_rhs = p_rhs->next;
		}
	}
}

// операции дл€ добавлени€ величины в конец и начало списка
//в конец
template <typename T>
void LinkedList<T>::push_tail(const T& elem) {
	Node<T>* new_node = new Node<T>;
	new_node->value = elem;
	new_node->next = nullptr;
	new_node->prev = get_tail();
	get_tail()->next = new_node;
	_tail = new_node;
}

//в начало
template <typename T>
void LinkedList<T>::push_head(const T& elem) {
	Node<T>* new_node = new Node<T>;
	new_node->value = elem;
	new_node->prev = nullptr;
	new_node->next = get_head();
	get_head()->prev = new_node;
	_head = new_node;
}

//операции дл€ склейки списков
//список cpy клеим в начало
template <typename T>
void LinkedList<T>::push_head(const LinkedList<T>& list){
	Node<T>* p1 = list.get_head();
	//ƒелаем копию списка list в динамической пам€ти и присоедин€ем его к исходному
	Node<T>* p2 = 


}

//список cpy клеим в конец



template <typename T>
T LinkedList<T>::pop_head() {
	Node<T>* p = get_head();
	_head = _head->next;
	T tmp = p->value;
	delete p;
	p = nullptr;
	return tmp;
}

template <typename T>
T LinkedList<T>::pop_tail() {
	Node<T>* p = get_tail();
	_tail = _tail->prev;
	T tmp = p->value;
	delete p;
	p = nullptr;
	return tmp;
}

template <typename T>
void LinkedList<T>::delete_node(const T& val) {
	Node<T>* p = get_head();
	while (p) {
		if (p->value == val){}
		p = p->next;
	}
	throw std::invalid_argument("There isn`t any nodes with asked value!")
}

// ќператор по индексу
template <typename T>
const T LinkedList<T>::operator[](const int ind) const{
	if (ind < 0) {
		throw std::invalid_argument("List index is negative!");
	}
	size_t tmp = 0;
	Node<T>* p = get_head();
	while (p) {
		if (tmp == ind) {
			return p->value;
		}
		p = p->next;
		++tmp;
	}

	throw std::invalid_argument("List index out of range!");
}

template <typename T>
T& LinkedList<T>::operator[](const int ind){
	if (ind < 0) {
		throw std::invalid_argument("List index is negative!");
	}
	size_t tmp = 0;
	Node<T>* p = get_head();
	while (p) {
		if (tmp == ind) {
			return p->value;
		}
		p = p->next;
		++tmp;
	}

	throw std::invalid_argument("List index out of range!");
}
#endif