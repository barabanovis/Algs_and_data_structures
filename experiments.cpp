#include "experiments.h"
#include "Set.h"
#include <ctime>

using namespace std;

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

Set random_set(size_t size) {
	Set res;
	for (size_t i = 0; i < size; i++) {
		res.insert(lcg());
	}
	return res;
}


double average_fill_time(size_t size, size_t attempts) {
	double res = 0;
	for (size_t attempt=0; attempt < attempts; ++attempt) {
		clock_t start = clock();
		Set test_set = random_set(size);
		clock_t end = clock();
		res += (double)(end - start);
	}
	return res / attempts;
}

double average_find_time(size_t size, size_t attempts) {
	double res = 0;
	Set test_set = random_set(size);
	for (size_t attempt = 0; attempt < attempts; ++attempt) {
		clock_t start = clock();
		test_set.contains(lcg());
		clock_t end = clock();
		res += (double)(end - start);
	}
	return res / attempts;
}

double average_insert_time(size_t size, size_t attempts) {
	double res = 0;
	Set test_set = random_set(size);
	for (size_t attempt = 0; attempt < attempts; ++attempt) {
		clock_t start = clock();
		test_set.insert(lcg());
		clock_t end = clock();
		res += (double)(end - start);
	}
	return res / attempts;
}

double average_erase_time(size_t size, size_t attempts) {
	double res = 0;
	Set test_set = random_set(size);
	for (size_t attempt = 0; attempt < attempts; ++attempt) {
		clock_t start = clock();
		test_set.erase(lcg());
		clock_t end = clock();
		res += (double)(end - start);
	}
	return res / attempts;
}