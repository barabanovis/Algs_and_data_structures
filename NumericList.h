#ifndef NUMERIC_LISTS_H
#define NUMERIC_LISTS_H

#include "LinkedList.h"

template <typename T>
concept NumericType = std::same_as<T, bool> ||
std::same_as<T, char>;

template <NumericType T>
LinkedList<T> numeric_addition(const LinkedList<T>& x, const LinkedList<T>& y);

template <NumericType T, typename mult_T>
LinkedList<T> operator*(const mult_T mult, const LinkedList<T>& x);

template <typename mult_T>
LinkedList<char> operator*(const mult_T mult, const LinkedList<char>& x) {
	LinkedList<char> result;
	char tmp = (char)mult;
	char transit = 0;
	Node<char>* p_x = x.get_tail();
	while (p_x) {
		char cur = transit + (p_x->value) * tmp;
		transit = cur / 10;
		cur = cur % 10;
		result.push_head(cur);
		p_x = p_x->prev;
	}

	while (transit > 0) {
		result.push_head(transit % 10);
		transit /= 10;
	}
	return result;
}

template <typename mult_T>
LinkedList<bool> operator*(const mult_T mult, const LinkedList<bool>& x)
{
	if ((bool)mult) {
		return x;
	}
	else {
		LinkedList<bool> empty_bool_list;
		return empty_bool_list;
	}
}

template <NumericType T, typename mult_T>
LinkedList<T> operator*(const LinkedList<T>& x, const mult_T mult) {
	return (mult * x);
}



template <NumericType T>
LinkedList<T> numeric_multiplication(const LinkedList<T>& x, const LinkedList<T>& y) {
	if (x.is_empty() || y.is_empty()) {
		LinkedList<T> null_list;
		null_list.push_head(0);
		return null_list;
	}

	LinkedList<T> result;
	Node<T>* p_y = y.get_tail();
	size_t digit_number = 0;
	while (p_y) {
		LinkedList<T> tmp = x * (p_y->value);
		for (size_t i = 0; i < digit_number; ++i) {
			tmp.push_tail(0);
		}
		result = numeric_addition(result, tmp);
		p_y = p_y->prev;
		digit_number++;
	}
	return result;
}

#endif