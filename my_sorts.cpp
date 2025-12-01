#include "my_sorts.h"
#include "LinkedList/NumericList.h"

using namespace std;


stats stats::operator+=(const stats rhs) {
	comparison_count += rhs.comparison_count;
	copy_count += rhs.copy_count;
	return *this;
}

stats operator+(const stats lhs, const stats rhs) {
	stats res = lhs;
	return res += rhs;
}

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
/*
	Здесь и всюду далее будем полагать, что сортируемый массив есть подпоследовательность
	с индексами [start,end]
*/
stats quick_sort(std::vector<int>& seq, const size_t start, const size_t end) {
	stats stat;
	if (end <= start) {
		return stat;
	}
	/*
	Можно также рассмотреть случай n=2 как тривиальный
	*/
	if (end - start == 1) {
		stat.comparison_count++;
		if (seq[end] < seq[start]) {
			stat.copy_count += 3;
			swap(seq[end], seq[start]);
		}
		return stat;
	}


	//В качестве опорного элемента выбирается первый (для определенности) поэтому
	// в дальнейшем будем полагать его за seq[start]

	size_t i = start + 1;
	size_t j = end;
	
	while (j - i > 0) {
		stat.comparison_count++;
		while (j > start && seq[j] > seq[start]) {
			j--;
		}

		stat.comparison_count++;
		if (j == start) {
			return stat;
		}

		stat.comparison_count++;
 		while (i < end && seq[i] < seq[start]) {
			i++;
		}
		if (i < j) {
			swap(seq[i], seq[j]);
		}
	}

	
	cout << "\n_____________________\n";
	cout << "anchor = " << seq[start] << " moved with " << seq[j] << '\n';
	

	stat.copy_count += 3;
	swap(seq[start], seq[j]);
	
	cout << seq;
	
	if (j > start) {
		stat += quick_sort(seq, start, j - 1);
		cout << "[" << start << "," << j - 1 << "]";
	}
	if (j < end) {
		stat += quick_sort(seq, j + 1, end);
		cout << " and [" << j + 1 << ", " << end << "]";
	}
	cout << "\n_____________________\n";
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