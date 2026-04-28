#ifndef FILEWORKING_H
#define FILEWORKING_H

#include <iostream>;
#include <string>
#include <filesystem>
#include <fstream>

struct Experiment {
	int table_start_capacity;
	int collisions;

	Experiment() :table_start_capacity(0), collisions(0) {};
	Experiment(size_t table_start_capacity, int collisions) : table_start_capacity(table_start_capacity), collisions(collisions) {};
};

Experiment one_experiment(const int table_capacity, const size_t group_count);

// функция 100 экспериментов над одним и тем же размером хеш-таблицы
void sub_experiment(const size_t table_capacity, const std::string& experiments_path, const std::string& probab_path, const size_t group_count);

void all_experiments();

bool create_file_with_directory(const std::string& filepath);

bool write_exp_results(Experiment exp, const std::string& filepath);

bool write_probability(const int table_cap, const double p, const std::string& filepath);

#endif