#ifndef MONOTONE_IMAGE_H
#define MONOTONE_IMAGE_H

#include <iostream>
#include "random_number.h"
#include <limits>

template <typename T>
class Image {
private:
	std::size_t _rows;
	std::size_t _columns;
	T* _matrix;

	const static double _eps;

	T* get_matrix() const;
public:
	Image(const size_t rows, const size_t columns, const bool random_fill); // Создаёт нулевую матрицу заданной размерности
	Image(const Image& cpy);

	~Image(void);
	
	size_t get_rows() const;
	size_t get_columns() const;
	


	T& operator()(const int row, const int column);
	const T operator()(const int row, const int column) const;

	bool operator==(const Image& rhs) const;
	bool operator!=(const Image& rhs) const;

	Image<T>& operator+=(const Image& rhs);
	Image<T> operator+(const Image& rhs);

	Image<T>& operator-=(const Image& rhs);
	Image<T> operator-(const Image& rhs);

	Image<T>& operator*=(const T rhs);
	Image<T> operator*(const T rhs);

	
	Image<T> operator!();

	float fill_coefficient() const;
};

template <typename T>
const double Image<T>::_eps = 1e-6;

// Специализации конструктора для каждого из типов данных
//bool
template<>
Image<bool>::Image(const size_t rows, const size_t columns, const bool random_fill) : _rows(rows), _columns(columns) {
	_matrix = new bool[rows * columns];

	bool* ptr = _matrix;

	if (random_fill) {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = random_bool();
		}
	}
	else {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = false;
		}
	}
}

//float
template<>
Image<float>::Image(const size_t rows, const size_t columns, const bool random_fill) : _rows(rows), _columns(columns) {
	_matrix = new float[rows * columns];

	float* ptr = _matrix;

	if (random_fill) {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = random_float();
		}
	}
	else {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = 0;
		}
	}
}

//char
template<>
Image<char>::Image(const size_t rows, const size_t columns, const bool random_fill) : _rows(rows), _columns(columns) {
	_matrix = new char[rows * columns];

	char* ptr = _matrix;

	if (random_fill) {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = random_char();
		}
	}
	else {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = 0;
		}
	}
}

//short
template<>
Image<short>::Image(const size_t rows, const size_t columns, const bool random_fill) : _rows(rows), _columns(columns) {
	_matrix = new short[rows * columns];

	short* ptr = _matrix;

	if (random_fill) {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = random_short();
		}
	}
	else {
		for (size_t i = 0; i < rows * columns; ++i, ptr++) {
			*ptr = 0;
		}
	}
}

template <typename T>
T* Image<T>::get_matrix() const {
	return _matrix;
}

template <typename T>
size_t Image<T>::get_columns() const {
	return _columns;
}

template <typename T>
size_t Image<T>::get_rows() const {
	return _rows;
}

template <typename T>
T& Image<T>::operator()(const int row, const int column) {
	if (row >= _rows || row < 0) {
		throw std::out_of_range("Invalid row index!");
	}
	if (column >= _columns || column < 0) {
		throw std::out_of_range("Invalid column index!");
	}
	return _matrix[row * _columns + column];
}

template <typename T>
const T Image<T>::operator()(const int row, const int column) const {
	if (row >= _rows || row < 0) {
		throw std::out_of_range("Invalid row index!");
	}
	if (column >= _columns || column < 0) {
		throw std::out_of_range("Invalid column index!");
	}
	return _matrix[row * _columns + column];
}

template <typename T>
Image<T>::Image(const Image& cpy) :_rows(cpy.get_rows()), _columns(cpy.get_columns()) {
	T* cpy_matrix = cpy.get_matrix();

	_matrix = new T[_rows * _columns];
	for (size_t i = 0; i < _rows * _columns; ++i) {
		_matrix[i] = cpy_matrix[i];
	}
}

template <typename T>
Image<T>::~Image(void) {
	if (_matrix) {
		delete[] _matrix;
	}
	_matrix = nullptr;
}

std::size_t max(const std::size_t a, const std::size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

std::size_t min(const std::size_t a, const std::size_t b) {
	if (a < b) {
		return a;
	}
	return b;
}

template <typename T>
bool Image<T>::operator==(const Image& rhs) const {
	if (_rows != rhs.get_rows()) {
		throw std::invalid_argument("Count of rows not equal!");
	}
	if (_columns != rhs.get_columns()) {
		throw std::invalid_argument("Count of columns not equal!");
	}

	T* rhs_matrix = rhs.get_matrix();

	for (size_t i = 0; i < _rows * _columns; ++i) {
		if (_matrix[i] - rhs_matrix[i] > _eps) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool Image<T>::operator!=(const Image& rhs) const {
	return !(*this == rhs);
}

template <typename T>
Image<T>& Image<T>::operator+=(const Image& rhs) {
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<T> result(res_rows, res_columns, false);

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			result(i, j) = 0;

			if (i < this->get_rows() && j < this->get_columns()) {
				result(i, j) += (*this)(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				result(i, j) += rhs(i, j);
			}
		}
	}
	*this = result;
	return *this;
}

template <typename T>
Image<T> Image<T>::operator+(const Image& rhs) {
	return (*this) += rhs;
}



template <typename T>
Image<T>& Image<T>::operator-=(const Image& rhs) {
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<T> result(res_rows, res_columns, false);

	size_t end_row = min(this->get_rows(), rhs.get_rows());
	size_t end_column = min(this->get_columns(), rhs.get_columns());

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			result(i, j) = 0;

			if (i < this->get_rows() && j < this->get_columns()) {
				result(i, j) += (*this)(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				result(i, j) -= rhs(i, j);
			}
		}
	}
	*this = result;
	return *this;
}

template <typename T>
Image<T> Image<T>::operator-(const Image& rhs) {
	return (*this) -= rhs;
}

template <typename T>
Image<T>& Image<T>::operator*=(const T rhs) {
	for (size_t i = 0; i < _columns * _rows; ++i) {
		_matrix[i] += rhs;
	}
	return *this;
}

template <typename T>
Image<T> Image<T>::operator*(const T rhs) {
	return (*this) *= rhs;
}

template <typename T>
float Image<T>::fill_coefficient() const {
	float res = 0;
	for (size_t i = 0; i < _rows * _columns; ++i) {
		res += (_matrix[i] / (get_rows() * get_columns() * std::numeric_limits<T>::max()));
	}
	return res;
}

template <typename T>
Image<T> Image<T>::operator!() {
	Image<T> result(*this);
	T* res_matrix = result.get_matrix();
	for (size_t i = 0; i < _rows * _columns; ++i) {
		_matrix[i] = std::numeric_limits<T>::max() - _matrix[i];
	}
	return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Image<T>& im) {

	// first row
	
	for (int j = 0; j < im.get_columns(); ++j) {
		os << im(0, j) << " ";
	}
	

	//rows 2->(n-1)
	for (int i = 1; i < im.get_rows() - 1; ++i) {
		os << " ";
		for (int j = 0; j < im.get_columns(); ++j) {
			os << im(i, j) << " ";
		}
		os << " \n";
	}

	if (im.get_rows() > 1) {
		//last row
		int last_row = (int)im.get_rows() - 1;
		os << " ";
		for (int j = 0; j < im.get_columns(); ++j) {
			os << im(last_row, j) << " ";
		}
		os << " \n";
	}
	return os;
}



#endif

