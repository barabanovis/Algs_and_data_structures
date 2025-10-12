#ifndef MODULED_OPERATIONS_H
#define MODULED_OPERATIONS_H

#include <iostream>

template <typename T>
bool is_valid_number(const T x) {
	if (x < 0 || x > 255) return false;
	return true;
}

template <>
bool is_valid_number(const char x) {
	if (x < 0 || x >128) return false;
	return true;
}

template <typename T>
T addit_mod(const T x, const T y) {
	if (!is_valid_number(x)) {
		throw std::invalid_argument("First argument is not in [0,255]");
	}
	if (!is_valid_number(y)) {
		throw std::invalid_argument("Second argument is not in [0,255]");
	}

	float tmp = x + y;
	if (tmp >= 255) {
		return 255;
	}
	return (T)tmp;
}

template <>
char addit_mod(const char x, const char y) {
	if (!is_valid_number(x)) {
		throw std::invalid_argument("First argument is not in [0,254]");
	}
	if (!is_valid_number(y)) {
		throw std::invalid_argument("Second argument is not in [0,254]");
	}

	float tmp = x + y;
	if (tmp >= 127) {
		return 127;
	}
	return tmp;
}

template <typename T>
T substr_mod(const T x, const T y) {
	if (!is_valid_number(x)) {
		throw std::invalid_argument("First argument is not in [0,254]");
	}
	if (!is_valid_number(y)) {
		throw std::invalid_argument("Second argument is not in [0,254]");
	}

	float tmp = x - y;
	if (tmp < 0) {
		return 0;
	}
	return tmp;
}

template <typename T>
T mult_mod(const T x, const T y) {
	if (!is_valid_number(x)) {
		throw std::invalid_argument("First argument is not in [0,254]");
	}
	if (!is_valid_number(y)) {
		throw std::invalid_argument("Second argument is not in [0,254]");
	}

	float tmp = x * y;
	if (tmp >= 255) {
		return 255;
	}
	return tmp;
}

template <>
char mult_mod(const char x, const char y) {
	if (!is_valid_number(x)) {
		throw std::invalid_argument("First argument is not in [0,254]");
	}
	if (!is_valid_number(y)) {
		throw std::invalid_argument("Second argument is not in [0,254]");
	}

	float tmp = x * y;
	if (tmp >= 127) {
		return 127;
	}
	return (char)tmp;
}

#endif