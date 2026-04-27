#ifndef FILEWORKING_H
#define FILEWORKING_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include "experiment.h"

bool create_file_with_directory(const std::string& filepath);

bool write_exp_results(const Experiment& exp, const std::string& filepath);

#endif