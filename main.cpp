#include "ios_start.h"
#include "NumericList.h"
#include "my_sorts.h"
#include "random_vector.h"
using namespace std;

void f(const int n) {
	vector<int> vect(n);
	for (int i = 0; i < n; i++) {
		vect[i] = n-i;
	}
	stats stat = shaker_sort(vect);
	cout << stat.copy_count << "\t" << stat.comparison_count << '\n';
}


int main() {
	ios_start();
	
	
	f(1000);
	f(2000);
	f(3000);
	f(10000);
	f(20000);
	f(50000);
	return 0;
}