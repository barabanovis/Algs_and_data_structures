#ifndef MONOTONE_IMAGE_H
#define MONOTONE_IMAGE_H

#include <iostream>


template <typename T>
class Image {
private:
	std::size_t _rows;
	std::size_t _columns;
	T* _matrix;

	static double eps = 1e-3;

	T* get_matrix() const;
public:
	Image(const size_t rows, const size_t columns, const bool random_fill); // Создаёт нулевую матрицу заданной размерности
	Image(const Image& cpy);

	~Image();
	
	size_t get_rows() const;
	size_t get_columns() const;
	


	T& operator()(const int row, const int column);
	const T& operator()(const int row, const int column) const;

	bool operator==(const Image& rhs) const;
	bool operator!=(const Image& rhs) const;
};

#endif

