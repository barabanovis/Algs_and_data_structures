#include "Monotone_Image.h"
#include "ios_start.h"
#include <iostream>

using namespace std;

struct LineCoeffs {
	int A;
	int B;
	int C;
};

int line_delta(const int x, const int y,const LineCoeffs& line_l) {
	return (line_l.A * x + line_l.B * y + line_l.C);
}

//Получение коэффициентов прямой A, B, C;
LineCoeffs get_coeffs(const int x1, const int y1, const int x2, const int y2){
	LineCoeffs res = { 0,0,0 };
	// См. каноническое и и не каноническое ур-е прямой
	// в декартовой ортонормированной с.к. пространства R^2
	res.A = y2 - y1;
	res.B = -x2 + x1;
	res.C = -x1 * y2 + x1 * y1 + x2 * y1 - x1 * y1;
	return res;
}

template <typename T>
Image<T> inverse_under_line(const Image<T>& image, const int x1, const int y1, const int x2, const int y2) {
	LineCoeffs line_l = get_coeffs(x1,y1,x2,y2);

	if (line_l.B == 0) {
		throw std::invalid_argument("Line is vertical, there isn`t higher side!");
	}

	Image<T> result(image);

	for (size_t j = 0; j < image.get_columns(); ++j) {
		int end = -(line_l.A / line_l.B) * (int)j - (line_l.C / line_l.B);

		if (end < 0){
			end = image.get_rows();
		}
		else if (end > image.get_rows()) {
			end = image.get_rows();
		}

		for (size_t i = 0; i < end; ++i) {
			result(i, j) = inverse(result(i, j));
		}
	}
	return result;
}

int main() {
	ios_start();
	
	const Image<char> imag(3, 4, true);

	cout << imag;
	cout << "____________\n";
	cout << inverse_under_line(imag, 2, 3, 6, 7);
	

	return 0;
}