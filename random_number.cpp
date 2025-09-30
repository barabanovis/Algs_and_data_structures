#include "random_number.h"
#include <iostream>
#include <random>
#include <ctime>
#include <limits>

using namespace std;


std::mt19937 gen(time(NULL));
std::uniform_int_distribution<> bool_distrib(0, 1);
std::uniform_real_distribution<> float_distrib(0, numeric_limits<float>::max());
std::uniform_int_distribution<> char_distrib(0, 255);
std::uniform_int_distribution<> short_distrib(0, numeric_limits<short>::max());

bool random_bool(void) {
	return (bool)bool_distrib(gen);
}

float random_float(void) {
	return (float)float_distrib(gen);
}

char random_char(void) {
	return (char)char_distrib(gen);
}

short random_short(void) {
	return (short)short_distrib(gen);
}