#ifndef MY_SORTS_H
#define MY_SORTS_H

#include <iostream>
#include <vector>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;

	stats operator+=(const stats rhs);
};

stats operator+(const stats lhs, const stats rhs);

// √руппа 1
stats insert_sort(std::vector<int>& seq);

// √руппа 2
stats shaker_sort(std::vector<int>& seq);

// √руппа 3
stats quick_sort(std::vector<int>& seq,const int start,const int end);

std::ostream& operator<<(std::ostream& os, const stats& stat);
#endif