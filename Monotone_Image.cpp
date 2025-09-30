#include "Monotone_Image.h"
#include "random_number"
#include <random>
#include <ctime>
#include <limits>

using namespace std;


// Специализации конструктора для каждого из типов данных
//bool
template<>
Image<bool>::Image(const size_t rows, const size_t columns, const bool random_fill) {
	_rows = rows;
	_columns = columns;

	_matrix = new bool[rows * columns];

	if (random_fill) {
		for (auto u : *_matrix) {
			
			u = ;
		}
	}
	else {
		for (auto u : *_matrix) {
			u = false;
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

template <typename T>
Image<T>& Image<T>::operator+=(const Image& rhs) {
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<T> result(res_rows, res_columns,false);

	size_t end_row = min(this->get_rows(), rhs.get_rows());
	size_t end_column = min(this->get_columns(), rhs.get_columns());

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			result(i, j) = 0;
			
			if (i < this->get_rows() && j < this->get_columns()) {
				result(i, j) += *this(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				result(i, j) += rhs(i, j);
			}
		}
	}
}

template <typename T>
Image<T> Image<T>::operator+(const Image& rhs) const{
	return (*this) += rhs;
}

template <typename T>
Image<T>& Image<T>::operator-=(const Image& rhs){
	size_t res_rows = max(this->get_rows(), rhs.get_rows());
	size_t res_columns = max(this->get_columns(), rhs.get_columns());
	Image<T> result(res_rows, res_columns, false);

	size_t end_row = min(this->get_rows(), rhs.get_rows());
	size_t end_column = min(this->get_columns(), rhs.get_columns());

	for (size_t i = 0; i < res_rows; ++i) {
		for (size_t j = 0; j < res_columns; ++j) {
			result(i, j) = 0;

			if (i < this->get_rows() && j < this->get_columns()) {
				result(i, j) += *this(i, j);
			}

			if (i < rhs.get_rows() && j < rhs.get_columns()) {
				result(i, j) -= rhs(i, j);
			}
		}
	}
}

template <typename T>
Image<T> Image<T>::operator-(const Image& rhs) const {
	return (*this) -= rhs;
}

template <typename T>
Image<T>& Image<T>::operator*=(const T rhs) {
	for (auto& u : *_matrix) {
		u = u * rhs;
	}
	return *this;
}

template <typename T>
Image<T> Image<T>::operator*(const T rhs) const {
	return (*this) *= rhs;
}

template <typename T>
float Image<T>::fill_coefficient() const {
	float res = 0;
	for (auto u : *_matrix) {
		res += (u / (get_rows() * get_columns() * numeric_limits<T>::max()));
	}
	return res;
}

template <typename T>
Image<T> Image<T>::operator!() {
	Image<T> result(*this);
	T* res_matrix = result.get_matrix();
	for (auto& u : *res_matrix) {
		u = numeric_limits<T>::max() - u;
	}
	return result;
}

template <typename T>
std::ostream& operator<<(std::ostream os, const Image<T>& im) {

	// first row
	os << "┏ ";
	for (size_t j = 0; j < im..get_columns(); ++j) {
		os << im(i, j) << " ";
	}
	os << " ┓\n"

		//rows 2->(n-1)
		for (size_t i = 1; i < im.get_rows() - 1; ++i) {
			os << "┃ "
				for (size_t j = 0; j < im.get_columns(); ++j) {
					os << im(i, j) << " ";
				}
			os << " ┃\n"
		}
	//last row
	os << "┗ ";
	for (size_t j = 0; j < im.get_rows(); ++j) {
		os << im(i, j) << " ";
	}
	os << " ┛\n";
	return os;
}