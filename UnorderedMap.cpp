#include "UnorderedMap.h"
#include <iostream>

using namespace std;

UnorderedMap::UnorderedMap(const size_t size) {
	_table = new Node[size];
}