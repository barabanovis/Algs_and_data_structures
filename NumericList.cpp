#include "NumericList.h"

using namespace std;

template <>
LinkedList<char> numeric_addition(const LinkedList<char>& x, const LinkedList<char>& y) {
	LinkedList<char> result = x;

	if (y.is_empty()) {
		return x;
	}
	if (x.is_empty()) {
		return y;
	}

	Node<char>* p_y = y.get_tail();
	Node<char>* p_res = x.get_tail();

	char transit = 0;
	while (p_y) {
		char cur = (p_y->value) + (p_res->value) + transit;
		transit = cur / 10;
		cur = cur % 10;
		p_res->value = cur;

		if (!(p_res->prev) ) {
			Node<char>* new_node = new Node<char>;
			new_node->prev = nullptr;
			new_node->next = p_res;
			new_node->value = 0;
		}

		p_res = p_res->prev;
		p_y = p_y->prev;
	}
	return result;
}