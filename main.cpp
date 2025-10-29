#include "ios_start.h"
#include "NumericList.h"

using namespace std;

int main() {
	ios_start();

	LinkedList<char> x;
	x.push_head(1);
	x.push_head(1);
	x.push_head(1);

	LinkedList<bool> y;
	y.push_head(0);
	y.push_head(1);

	LinkedList<char> z = 67*x;

	cout << x;
	cout << y;
	cout << z;

	return 0;
}