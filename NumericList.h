#ifndef NUMERIC_LISTS_H
#define NUMERIC_LISTS_H

#include "LinkedList.h"

template <typename T>
concept NumericType = std::same_as<T, bool> ||
std::same_as<T, char>;

template <NumericType T>
LinkedList<T> numeric_addition(const LinkedList<T>& x, const LinkedList<T>& y);

template <NumericType T>
LinkedList<T> numeric_multiplication(const LinkedList<T>& x, const LinkedList<T>& y);

#endif