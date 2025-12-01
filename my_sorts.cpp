#include "my_sorts.h"
#include "LinkedList/NumericList.h"

using namespace std;

//Вспомогательная ф-я превращения списка в вектор
vector<int> list_to_vect(LinkedList<int>& list) {
	vector<int> result(0);
	
	while (!list.is_empty()) {
		result.push_back(list.pop_head());
	}
	
	return result;
}


/*
// Группа 1
stats insert_sort(std::vector<int>& seq) {
	stats stats;
	

	for (size_t i = 1; i < seq.size(); ++i) {
		int tmp = seq[i];
		stats.copy_count++;

		// Находим позицию, в кот надо вставить
		int j = i - 1;
		while (j >= 0 && tmp < seq[j]) {
			stats.comparison_count++;
			seq[j + 1] = seq[j];
			stats.copy_count++;
			j--;
		}
		stats.comparison_count++;

		seq[j + 1] = tmp;
		stats.copy_count++;
	}
	return stats;
}
*/

// Группа 1
stats insert_sort(std::vector<int>& seq) {
	LinkedList<int> list(seq);

	stats stats;
	
	if (list.is_empty()) {
		return stats;
	}

	if (!(list.get_head()->next)) {
		return stats;
	}


	auto i = list.get_head()->next;
	while(i) {
		int tmp = i->value;
		stats.copy_count++;
		// Находим позицию, в кот надо вставить
		auto j = i->prev;
		while (j && (tmp < j->value)) {
			stats.comparison_count++;
			j->next->value = j->value;
			stats.copy_count++;
			j=j->prev;
		}
		stats.comparison_count++;

		if (j) {
			j->next->value = tmp;
		}
		else {
			list.get_head()->value = tmp;
		}
		stats.copy_count++;
		i = i->next;
	}

	seq = list_to_vect(list);
	return stats;
}



// Группа 2
stats shaker_sort(std::vector<int>& seq) {
	stats stats;
	if (seq.size() <= 1) {
		return stats;
	}

	

	size_t lb = 0;
	size_t rb = seq.size()-1;
	bool k = true;

	stats.comparison_count++;
	while (rb-lb>0){
		stats.comparison_count++;
		if (k) {
			for (size_t l = lb+1; l <= rb; l++) {
				stats.comparison_count++;
				if (seq[l-1] > seq[l]) {
					swap(seq[l], seq[l - 1]);
					stats.copy_count += 3;
				}
			}
			rb--;
		}
		else {
			for (size_t j = rb; j > lb; --j) {
				stats.comparison_count++;
				if (seq[j-1] > seq[j]) {
					stats.copy_count += 3;
					swap(seq[j], seq[j - 1]);
				}
			}
			lb++;
		}
		k=!k;
	}
	return stats;
}

// Группа 3
stats quick_sort(std::vector<int>& seq) {
	stats stat;

	return stat;
}

std::ostream& operator<<(std::ostream& os, const stats& stat) {
	os << "comparison_count = ";
	os << stat.comparison_count;
	os << '\n';
	os << "copy_count = ";
	os << stat.copy_count;
	os << '\n';
	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& seq) {
	for (auto u : seq) {
		os << u << " ";
	}
	os << '\n';
	return os;
}