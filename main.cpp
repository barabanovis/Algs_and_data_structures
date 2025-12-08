#include "ios_start.h"
#include "my_sorts.h"
#include "LinkedList\NumericList.h"
#include "experiment\random_vector.h"
using namespace std;

void experiment_reverse_sorted(int n, stats (*sort_func)(std::vector<int>& seq)) {
	vector<int> vect(n);
	
	for (int i = 0; i < n; i++) {
		vect[i] = n - i;
	}
	
	stats res = sort_func(vect);
	cout << n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
}


void experiment_random(const int n, stats(*sort_func)(std::vector<int>& seq)) {
	vector<int> vect = random_int_vector(n);

	stats res= sort_func(vect);
	cout <<n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
	
}

void experiment_sorted(const int n, stats(*sort_func)(std::vector<int>& seq)) {
	vector<int> vect(n);
	for (size_t i = 0; i < n; i++) {
		vect[i] = i;
	}

	stats res = sort_func(vect);
	cout << n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
}

int main() {
	ios_start();

	for (int k = 1; k <= 50; k++) {
		experiment_reverse_sorted(1000 * k,insert_sort);
	}
	
	return 0;
}