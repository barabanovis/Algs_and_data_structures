#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList<float> lst1;
	lst1.push_tail(1.005);
	lst1.push_head(2.8);
	lst1.push_tail(3.7);


	LinkedList<float> lst2;
	lst2.push_head(3.14);
	lst2.push_head(5.5);
	lst2.push_head(6.6);

	lst1.push_head(lst2);
	for (size_t i = 0; i < 6; ++i) {
		cout << lst1[i] << " ";
	}

	return 0;
}