#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

#include <iostream>
#include <random>
#include <ctime>
#include <limits>

template <typename T>
concept NumericType = std::same_as<T, short> ||
std::same_as<T, float> ||
std::same_as<T, bool> ||
std::same_as<T, char> ||
std::same_as<T, int>;


std::mt19937 gen(time(NULL));
std::uniform_int_distribution<> bool_distrib(0, 1);
std::uniform_real_distribution<> float_distrib(0, 255);
std::uniform_int_distribution<> char_distrib(0, 127);
std::uniform_int_distribution<> short_distrib(0, 255);

template <NumericType T>
T random_element(const T& x);

template<>
bool random_element(const bool& x) {
	return (bool)bool_distrib(gen);
}

template<>
float random_element(const float& x) {
	return (float)float_distrib(gen);
}

template<>
char random_element(const char& x) {
	return (char)char_distrib(gen);
}

template<>
short random_element(const short& x) {
	return (short)short_distrib(gen);
}

template<>
int random_element(const int& x) {
	return (int)short_distrib(gen);
}

#endif