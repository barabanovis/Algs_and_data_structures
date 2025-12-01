#include "random_vector.h"
#include <vector>
#include <random>
#include <ctime>

std::vector<int> random_int_vector(const int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 1000);

    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = distrib(gen);
    }
    return result;
}
