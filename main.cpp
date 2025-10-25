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
			end = 0;
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
	
	//Демонстранционный main
	//Сложение одинаковых матриц
	{
		Image<float> imag1(4, 4, true);
		Image<float> imag2(4, 4, true);

		cout << "imag1\n" << imag1;
		cout << "______________________\nimag2\n" << imag2;
		cout << "______________________\nimag1+imag2\n";
		cout << imag1 + imag2;
		cout << "_______________________\n";
	}
	cout << "**********************************\n";

	//Сложение разных матриц
	{
		Image<short> imag3(5, 1, true);
		Image<short> imag4(2, 7, true);

		cout << "imag3\n" << imag3;
		cout << "______________________\nimag4\n" << imag4;
		cout << "______________________\nimag3+imag4\n";
		cout << imag3 + imag4;
		cout << "_______________________\n";
	}
	cout << "**********************************\n";

	//Вычитание одинаковых матриц
	{
		Image<bool> imag5(8, 8, true);
		Image<bool> imag6(8, 8, true);

		cout << "imag5\n" << imag5;
		cout << "______________________\nimag6\n" << imag6;
		cout << "______________________\nimag5-imag6\n";
		cout << imag5 - imag6;
		cout << "_______________________\n";
	}
	cout << "**********************************\n";

	//Вычитание разных матриц
	{
		Image<char> imag7(5, 8, true);
		Image<char> imag8(9, 3, true);

		cout << "imag7\n" << imag7;
		cout << "______________________\nimag8\n" << imag8;
		cout << "______________________\nimag5-imag6\n";
		cout << imag7 - imag8;
		cout << "_______________________\n";
	}
	cout << "**********************************\n";

	//Умножение матрицы на скаляр
	{
		Image<short> imag9(3, 4, true);
		cout << "imag9\n" << imag9;
		cout << "_________________\n5*imag9\n";
		cout << 5 * imag9;
		cout << "_________________\n";
	}
	cout << "**********************************\n";

	//Поэлементное умножение матриц
	{
		Image<short> imag11(5, 5, true);
		Image<short> imag12(5, 5, true);
		cout << "imag11\n" << imag11;
		cout << "_________________\n";
		cout << "imag12\n" << imag12;
		cout << "_________________\n";
		cout << imag11 * imag12;
		cout << "_________________\n";
	}
	cout << "**********************************\n";

	//Инверсия матрицы
	{
		Image<char> imag10(6, 6, true);
		cout << "imag10\n" << imag10;
		cout << "_________________\n";
		cout << "!imag10\n" << !imag10;
		cout << "_________________\n";
	}
	cout << "**********************************\n";

	//Коэффициент заполнения матрицы
	{
		Image<float> imag13(7, 7, true);
		cout << "imag13\n" << imag13;
		cout << "_________________\n";
		cout << "imag13: fill_coefficient = " << imag13.fill_coefficient() << '\n';
		cout << "_________________\n";
	}
	cout << "**********************************\n";

	
	cout << "Example of solving task 6-4\n";
	cout << "Line points: (2,3), (6,7)\n";
	//Пример решения задачи (вариант 6, задача 4)
	const Image<char> imag(7, 9, true);

	cout << "imag\n";
	cout << imag;
	cout << "____________\nresult\n";
	cout << inverse_under_line(imag, 2, 3, 6, 7);
	

	return 0;
}