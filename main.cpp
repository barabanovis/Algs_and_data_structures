#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "experiments.h"
#include "Set.h"

using namespace std;

namespace fs = std::filesystem;

void experiments() {
	ofstream file("../../../statistics.txt");

	if (!file.is_open()) {
		throw std::runtime_error("Invalid file path!");
	}

	
	file << "Average fill time: (100 attempts)\n";
	cout << "Average fill time analyzing\n";
	file << "size = 1000: " << average_fill_time(1000, 10) << '\n';
	cout << "size = 1000 analyzed\n";
	file.flush();
	file << "size = 10000: " << average_fill_time(10000, 10) << '\n';
	cout << "size = 10000 analyzed\n";
	file.flush();
	file << "size = 100000: " << average_fill_time(100000, 1) << '\n';
	cout << "size = 100000 analyzed\n";
	file.flush();
	

	file << "Average find time: (1000 attempts)\n";
	cout << "Average find time analyzing\n";
	file << "size = 1000: " << average_find_time(1000, 1) << '\n';
	cout << "size = 1000 analyzed\n";
	file.flush();
	file << "size = 10000: " << average_find_time(10000, 1) << '\n';
	cout << "size = 10000 analyzed\n";
	file.flush();
	file << "size = 100000: " << average_find_time(100000, 1) << '\n';
	cout << "size = 100000 analyzed\n";
	file.flush();

	file << "Average insert time: (1000 attempts)\n";
	cout << "Average insert time analyzing\n";
	file << "size = 1000: " << average_insert_time(1000, 1) << '\n';
	cout << "size = 1000 analyzed\n";
	file.flush();
	file << "size = 10000: " << average_insert_time(10000, 1) << '\n';
	cout << "size = 10000 analyzed\n";
	file.flush();
	file << "size = 100000: " << average_insert_time(100000, 1) << '\n';
	cout << "size = 100000 analyzed\n";
	file.flush();

	file << "Average erase time: (1000 attempts)\n";
	cout << "Average erase time analyzing\n";
	file << "size = 1000: " << average_erase_time(1000, 1) << '\n';
	cout << "size = 1000 analyzed\n";
	file.flush();
	file << "size = 10000: " << average_erase_time(10000, 1) << '\n';
	cout << "size = 10000 analyzed\n";
	file.flush();
	file << "size = 100000: " << average_erase_time(100000, 1) << '\n';
	cout << "size = 100000 analyzed\n";
	file.flush();
	file.close();
}

vector<int> delete_repeating_elements(const vector<int>& start_v) {
	Set myset;
	for (auto u : start_v) {
		myset.insert(u);
	}
	return myset.to_vector();
}

void task_example() {
	vector<int> v = { 1,1,1,4,3,5,2,6,55,3,234,668,53,23,4 };
	vector<int> res = delete_repeating_elements(v);
	for (auto u : res) {
		cout << u << " ";
	}
}


int main() {
	/*
	Set myset;
	for (int i = 0; i < 100; i++) {
		myset.insert(i);
	}
	myset.print();
	myset.erase(8);
	myset.print();
	cout << '\n' << myset.strictly_balanced();*/
	experiments();
}