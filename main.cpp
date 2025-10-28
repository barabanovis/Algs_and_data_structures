#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList<int> lst1;
	lst1.push_tail(1);
	lst1.push_tail(2);
	lst1.push_tail(3);


	
	
	lst1[1] = 5;
	
	

	
	for (size_t i = 0; i < 3; ++i) {
		cout << lst1[i] << " ";
	}

	return 0;
}