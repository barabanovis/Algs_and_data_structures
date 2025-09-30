#include "Monotone_Image.h"
#include "ios_start.h"
#include <iostream>

using namespace std;

int main() {
	ios_start();
	Image<bool> imag1(9, 9, true);
	cout << imag1;
	cout << !imag1;
	return 0;
}