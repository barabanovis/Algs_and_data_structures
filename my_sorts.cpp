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
stats quick_sort(std::vector<int>& seq, const int start, const int end) {
	stats stat;

	// Базовые случаи
	stat.comparison_count++;
	if (end <= start) {
		return stat;
	}

	stat.comparison_count++;
	if (end - start == 1) {
		stat.comparison_count++;
		if (seq[end] < seq[start]) {
			stat.copy_count += 3;
			std::swap(seq[end], seq[start]);
		}
		return stat;
	}

	// Выбираем опорный элемент (фиксируем значение)
	const int pivot = seq[start];
	int i = start + 1;  // Левый указатель (идёт вправо)
	int j = end;        // Правый указатель (идёт влево)

	stat.comparison_count++;
	while (i <= j) {
		// Двигаем левый указатель вправо, пока элемент < pivot
		stat.comparison_count++;
		while (seq[i] < pivot) {
			stat.comparison_count++;
			i++;
		}
		// Если вышли за границы, корректируем
		stat.comparison_count++;
		if (i > end) {
			i = end;
		}

		// Двигаем правый указатель влево, пока элемент > pivot
		stat.comparison_count++;
		while (seq[j] > pivot) {
			stat.comparison_count++;
			j--;
		}

		// Если указатели не пересеклись, меняем элементы
		stat.comparison_count++;
		if (i <= j) {
			stat.comparison_count++;
			if (i != j) {
				stat.copy_count += 3;
				swap(seq[i], seq[j]);
			}
			i++;
			j--;
		}
	}

	// Размещаем pivot на правильное место
	stat.comparison_count++;
	if (j != start) {
		stat.copy_count += 3;
		std::swap(seq[start], seq[j]);
	}

	// Рекурсивно сортируем левую и правую части
	stats left = quick_sort(seq, start, i - 1);
	stats right = quick_sort(seq, i, end);

	stat += left;
	stat += right;

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