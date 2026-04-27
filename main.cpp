#include <iostream>
#include "UnorderedMap.h"
#include <string>
#include <random>

using namespace std;

int main() {
    UnorderedMap<float> my_map(30, 44);
    my_map.print();
}