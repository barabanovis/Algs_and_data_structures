#include "NumericList.h"

using namespace std;

template <>
LinkedList<char> numeric_addition(const LinkedList<char>& x, const LinkedList<char>& y) {
	LinkedList<char> result;

	if (y.is_empty()) {
		return x;
	}
	if (x.is_empty()) {
		return y;
	}

	Node<char>* p_y = y.get_tail();
	Node<char>* p_x = x.get_tail();

	char transit = 0;
	while (p_x || p_y) {
		char cur = transit;
		if (p_x) {
			cur += p_x->value;
		}
		if (p_y) {
			cur += p_y->value;
		}
		transit = cur / 10;
		cur = cur % 10;
		result.push_head(cur);

		if (p_x) {
			p_x = p_x->prev;
		}
		if (p_y) {
			p_y = p_y->prev;
		}
	}
	
	while (transit > 0) {
		result.push_head(transit % 10);
		transit = transit / 10;
	}

	return result;
}