#include "random_number.h"
#include <iostream>
#include <random>
#include <ctime>
#include <limits>

using namespace std;

bool random_bool(void) {
	mt19937 gen(time(0));
	uniform_int_distribution<> distrib(0, 1);

	return (bool)distrib(gen);
}

float random_float(void) {
	mt19937 gen(time(0));
	uniform_real_distribution<> distrib(0, numeric_limits<float>::max());

	return (float)distrib(gen);
}

char random_char(void) {
	mt19937 gen(time(0));
	uniform_int_distribution<> distrib(0, 255);

	return (char)distrib(gen);
}

short random_short(void) {
	mt19937 gen(time(0));
	uniform_int_distribution<> distrib(0, numeric_limits<short>::max());

	return (char)distrib(gen);
}