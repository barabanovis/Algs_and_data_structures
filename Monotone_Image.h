#ifndef MONOTONE_IMAGE_H
#define MONOTONE_IMAGE_H

#include <iostream>
#include "random_number.h"
#include "moduled_operations.h"

template <typename T>
concept NumericType = std::same_as<T, short> ||
	std::same_as<T, float> ||
	std::same_as<T, bool> ||
	std::same_as<T, char> ||
	std::same_as<T, int>;


template <NumericType im_T>
class Image {
private:
	std::size_t _rows;
	std::size_t _columns;
	im_T* _matrix;

	const static double _eps;

	im_T* get_matrix() const;
public:
	Image(const size_t rows, const size_t columns, const bool random_fill); // Создаёт нулевую матрицу заданной размерности
	Image(const Image& cpy);

	~Image(void) = default;
	
	size_t get_rows() const;
	size_t get_columns() const;
	


	im_T& operator()(const int row, const int column);
	const im_T operator()(const int row, const int column) const;

	bool operator==(const Image<im_T>& rhs) const;
	bool operator!=(const Image<im_T>& rhs) const;

	Image<im_T>& operator+=(const Image<im_T>& rhs);
	Image<im_T> operator+(const Image<im_T>& rhs) const;

	Image<im_T>& operator-=(const Image<im_T>& rhs);
	Image<im_T> operator-(const Image& rhs) const;

	template <NumericType num_T>
	Image<im_T>& operator*=(const num_T rhs);

	template <NumericType num_T>
	Image<im_T> operator*(const num_T rhs) const;

	Image<im_T> operator*=(const Image<im_T>& rhs);
	Image<im_T> operator*(const Image<im_T>& rhs) const;
	
	Image<im_T> operator!() const;

	float fill_coefficient() const;
};


template <NumericType im_T>
const double Image<im_T>::_eps = 1e-6;

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

template <NumericType im_T>
im_T* Image<im_T>::get_matrix() const {
	return _matrix;
}

template <NumericType im_T>
size_t Image<im_T>::get_columns() const {
	return _columns;
}

template <NumericType im_T>
size_t Image<im_T>::get_rows() const {
	return _rows;
}

template <NumericType im_T>
im_T& Image<im_T>::operator()(const int row, const int column) {
	if (row >= _rows || row < 0) {
		throw std::out_of_range("Invalid row index!");
	}
	if (column >= _columns || column < 0) {
		throw std::out_of_range("Invalid column index!");
	}
	return _matrix[row * _columns + column];
}

template <NumericType im_T>
const im_T Image<im_T>::operator()(const int row, const int column) const {
	if (row >= _rows || row < 0) {
		throw std::out_of_range("Invalid row index!");
	}
	if (column >= _columns || column < 0) {
		throw std::out_of_range("Invalid column index!");
	}
	return _matrix[row * _columns + column];
}

template <NumericType im_T>
Image<im_T>::Image(const Image& cpy) :_rows(cpy.get_rows()), _columns(cpy.get_columns()) {
	im_T* cpy_matrix = cpy.get_matrix();

	_matrix = new im_T[_rows * _columns];
	for (size_t i = 0; i < _rows * _columns; ++i) {
		_matrix[i] = cpy_matrix[i];
	}
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

template <NumericType im_T>
bool Image<im_T>::operator==(const Image<im_T>& rhs) const {
	if (_rows != rhs.get_rows()) {
		throw std::invalid_argument("Count of rows not equal!");
	}
	if (_columns != rhs.get_columns()) {
		throw std::invalid_argument("Count of columns not equal!");
	}

	im_T* rhs_matrix = rhs.get_matrix();

	for (size_t i = 0; i < _rows * _columns; ++i) {
		if (_matrix[i] - rhs_matrix[i] > _eps) {
			return false;
		}
	}
	return true;
}

template <NumericType im_T>
bool Image<im_T>::operator!=(const Image<im_T>& rhs) const {
	return !(*this == rhs);
}

template <NumericType im_T>
Image<im_T>& Image<im_T>::operator+=(const Image<im_T>& rhs) {
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<im_T> result(res_rows, res_columns, false);

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			im_T tmp = 0;

			if (i < this->get_rows() && j < this->get_columns()) {
				tmp = (*this)(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				tmp = addit_mod(tmp, rhs(i, j));
			}

			result(i, j) = tmp;
		}
	}
	*this = result;
	return *this;
}

template <NumericType im_T>
Image<im_T> Image<im_T>::operator+(const Image<im_T>& rhs) const {
	Image<im_T> result = (*this);
	result += rhs;
	return result;
}



template <NumericType im_T>
Image<im_T>& Image<im_T>::operator-=(const Image<im_T>& rhs) {
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<im_T> result(res_rows, res_columns, false);

	size_t end_row = min(this->get_rows(), rhs.get_rows());
	size_t end_column = min(this->get_columns(), rhs.get_columns());

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			im_T tmp = 0;

			if (i < this->get_rows() && j < this->get_columns()) {
				tmp += (*this)(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				tmp = substr_mod(tmp, rhs(i, j));
			}
			result(i, j) = tmp;
		}
	}
	*this = result;
	return *this;
}

template <NumericType im_T>
Image<im_T> Image<im_T>::operator-(const Image<im_T>& rhs) const{
	Image<im_T> result = (*this);
	result -= rhs;
	return result;
}

template <NumericType im_T>
template <NumericType num_T> 
Image<im_T>& Image<im_T>::operator*=(const num_T rhs) {
	for (size_t i = 0; i < _columns * _rows; ++i) {
		_matrix[i] = mult_mod(_matrix[i], (im_T)rhs);
	}
	return *this;
}

template <NumericType im_T>
template <NumericType num_T>
Image<im_T> Image<im_T>::operator*(const num_T rhs) const {
	Image<im_T> result = (*this);
	result *= (im_T)rhs;
	return result;
}

template <NumericType im_T>
Image<im_T> Image<im_T>::operator*=(const Image<im_T>& rhs) {
	//Поэлементное умножение мариц ==> матрицы одинаковых размеров
	if (this->get_columns() != rhs.get_columns()) {
		throw std::invalid_argument("Count of columns is not equal in arguments!");
	}
	if (this->get_rows() != rhs.get_rows()) {
		throw std::invalid_argument("Count of rows is not equal in arguments!");
	}

	for (size_t i = 0; i < get_rows(); ++i) {
		for (size_t j = 0; j < get_columns(); ++j) {
			(*this)(i, j) = mult_mod((*this)(i, j), rhs(i, j));
		}
	}
	return *this;
}

template <NumericType im_T>
Image<im_T> Image<im_T>::operator*(const Image<im_T>& rhs) const{
	Image<im_T> result(*this);
	result *= rhs;
	return result;
}

template <NumericType im_T, NumericType num_T>
Image<im_T> operator*(const num_T lhs, Image<im_T>& image) {
	Image<im_T> result(image);
	result *= (im_T)lhs;
	return result;
}

template <NumericType im_T>
float Image<im_T>::fill_coefficient() const {
	float tmp = 0;
	for (size_t i = 0; i < _rows * _columns; ++i) {
		tmp += _matrix[i];
	}
	return tmp / (get_rows() * get_columns() * 255);
}

template <>
float Image<char>::fill_coefficient() const {
	float tmp = 0;
	for (size_t i = 0; i < _rows * _columns; ++i) {
		tmp += _matrix[i];
	}
	return tmp / (get_rows() * get_columns() * 128);
}

template <typename T>
T inverse(const T x) {
	return (255 - x);
}

template <>
bool inverse(const bool x) {
	return !x;
}

template <>
char inverse(const char x) {
	return (128 - x);
}

template <NumericType im_T>
Image<im_T> Image<im_T>::operator!() const{
	Image<im_T> result(*this);
	im_T* res_matrix = result.get_matrix();
	for (size_t i = 0; i < _rows * _columns; ++i) {
		res_matrix[i] = inverse(res_matrix[i]);
	}
	return result;
}

template <NumericType im_T>
std::ostream& operator<<(std::ostream& os, const Image<im_T>& im) {
	for (int i = 0; i < im.get_rows(); ++i) {
		os << " ";
		for (int j = 0; j < im.get_columns(); ++j) {
			os << im(i, j) << " ";
		}
		os << " \n";
	}
	return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const Image<char>& im) {
	for (int i = 0; i < im.get_rows(); ++i) {
		os << " ";
		for (int j = 0; j < im.get_columns(); ++j) {
			os << (int)im(i, j) << " ";
		}
		os << " \n";
	}
	return os;
}



#endif

