#include "LinkedList.h"
#include "ios_start.h"

using namespace std;

int main() {
	ios_start();

	LinkedList<char> x;
	x.push_head(1);
	x.push_head(2);
	x.push_head(3);

	
	LinkedList<char> y;
	y.push_tail(5);
	y.push_tail(4);
	y.push_tail(7);
	

	cout << x;
	cout << y;

	return 0;
}