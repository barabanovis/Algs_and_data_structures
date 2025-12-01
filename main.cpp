#include "ios_start.h"
#include "LinkedList\NumericList.h"
#include "my_sorts.h"
#include "experiment\random_vector.h"
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
	
	int n;
	cin >> n;
	vector<int> vect(n);

	for (auto& u : vect) {
		cin >> u;
	}

	stats res = insert_sort(vect);
	cout << res;
	
	for (auto u : vect) {
		cout << u << " ";
	}
	
	return 0;
}