#include "Monotone_Image.h"
#include <random>
#include <ctime>

using namespace std;

template <typename T>
Image<T>::Image(const size_t rows, const size_t columns, const bool random_fill) {
	std::_rows = rows;
	std::_columns = columns;

	_matrix = new T[rows * columns];
	
	if (random_fill) {
		uniform_real_distribution 

		for (auto u : *_matrix) {
			u = ;
		}
	}
	else {
		for (auto u : *_matrix) {
			u = 0;
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
T& Image<T>::operator()(const int row, const int column){
	if (row > _rows || row < 0) {
		throw std::invalid_argument("Invalid row index!");
	}
	if (column > _columns || column < 0) {
		throw std::invalid_argument("Invalid column index!");
	}

	return _matrix[row * _columns + column];
}

template <typename T>
const T& Image<T>::operator()(const int row, const int column) const{
	if (row > _rows || row < 0) {
		throw std::invalid_argument("Invalid row index!");
	}
	if (column > _columns || column < 0) {
		throw std::invalid_argument("Invalid column index!");
	}

	return _matrix[row * _columns + column];
}

template <typename T>
Image<T>::Image(const Image& cpy) {
	_rows = cpy.get_rows();
	_columns = cpy.get_columns();

	cpy_matrix = cpy.get_matrix();

	_matrix = new T[_rows*_columns];
	for (size_t i = 0; i < _rows * _columns; ++i) {
		_matrix[i] = cpy_matrix[i];
	}
}

template <typename T>
Image<T>::~Image() {
	delete _matrix;
	delete _rows;
	delete _columns;
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
		if (_matrix[i] - rhs_matrix[i] > eps) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool Image<T>::operator!=(const Image& rhs) const{
	return !(*this == rhs);
}