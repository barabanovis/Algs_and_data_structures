#include "ios_start.h"
#include "NumericList.h"

using namespace std;

int main() {
	ios_start();

	LinkedList<char> x(0,9,10);
	

	LinkedList<char> y(0,7,13);


	LinkedList<char> z = numeric_multiplication(x, y);

	cout << x;
	cout << y;
	cout << z;
	return 0;
}