#include "ios_start.h"
#include "LinkedList\NumericList.h"
#include "my_sorts.h"
#include "experiment\random_vector.h"
using namespace std;



void experiment(const int n) {
	vector<int> vect = random_int_vector(n);

	stats res= insert_sort(vect);
	cout <<n << "\t" << res.copy_count << "\t" << res.comparison_count << '\n';
	
}

int main() {
	ios_start();
	
	for (int k = 1; k <= 50; k++) {
		experiment(1000 * k);
	}
	
	return 0;
}