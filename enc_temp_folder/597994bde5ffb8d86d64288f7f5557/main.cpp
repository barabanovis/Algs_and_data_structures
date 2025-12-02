#include "ios_start.h"
#include "my_sorts.h"
#include "LinkedList\NumericList.h"
#include "experiment\random_vector.h"
using namespace std;

void experiment_unsorted(int n) {
	vector<int> vect(n);
	
	for (int i = 0; i < n; i++) {
		vect[i] = n - i;
	}
	
	stats res = quick_sort(vect,0,n-1);
	cout << n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
}


void experiment_random(const int n) {
	vector<int> vect = random_int_vector(n);

	stats res= quick_sort(vect,0,n-1);
	cout <<n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
	
}

int main() {
	ios_start();
	
	

	
	for (int k = 1; k <= 50; k++) {
		experiment_unsorted(1000 * k);
	}
	
	
	
	
	return 0;
}