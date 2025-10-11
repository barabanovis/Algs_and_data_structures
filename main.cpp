#include "Monotone_Image.h"
#include "ios_start.h"
#include <iostream>

using namespace std;

int main() {
	ios_start();
	Image<char> imag1(9, 9, true);
	Image<char> imag2(9, 9, true);
	cout << imag1;
	cout << "____________________\n";
	cout << imag2;
	cout << "____________________\n";
	cout << (imag1 + imag2);
	return 0;
}