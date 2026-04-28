#include "fileworking.h"
#include "UnorderedMap.h"

using namespace std;

namespace fs = std::filesystem;

bool create_file_with_directory(const std::string& filepath) {
    try {
        // Получаем путь к директории из полного пути к файлу
        fs::path directory = fs::path(filepath).parent_path();

        // Создаём директорию (и все родительские, если нужно), если её нет
        if (!directory.empty() && !fs::exists(directory)) {
            fs::create_directories(directory);
            std::cout << "Created directory: " << directory << std::endl;
        }

        // Создаём файл
        std::ofstream file(filepath);
        if (!file) {
            std::cerr << "Error: cannot open file: " << filepath << std::endl;
            return false;
        }
        file.close();
        std::cout << "File created: " << filepath << std::endl;
        return true;
    }
    catch (const fs::filesystem_error& ex) {
        std::cerr << "Ошибка файловой системы: " << ex.what() << std::endl;
        return false;
    }
}

using namespace std;

struct Experiment;

Experiment one_experiment(const int table_capacity, const size_t group_count) {
    UnorderedMap<float> my_map(table_capacity, group_count, 1000);
    Experiment results;
    results.table_start_capacity = table_capacity;
    results.collisions = my_map.count_collisions();
    return results;
}

// Делает 100 замеров для постоянного размера таблицы
void sub_experiment(const size_t table_capacity, const string& experiments_path, const string& probab_path,const size_t group_count) {
    int count = 0; // счетчик числа отсчётов, где не было коллизий

    const int attempts_num = 1000;

    for (int attempt = 0; attempt < attempts_num; ++attempt) {
        Experiment exp = one_experiment(table_capacity, group_count);
        write_exp_results(exp, experiments_path);
        if (exp.collisions > 0) {
            count += 1;
        }
    }
    double probab = (double)count / attempts_num;
    write_probability(table_capacity, probab, probab_path);
}

void all_experiments() {
    const string experiments_path = "../../../results/experiments.csv";
    const string probab_path = "../../../results/probability.csv";
    const size_t group_count = 29;

    // Cоздание файлов для сохранения результатов
    create_file_with_directory(experiments_path);
    ofstream exp_file(experiments_path);
    if (!exp_file.is_open()) {
        throw std::invalid_argument("Unrorrect file_path!");
    }
    exp_file << "table_capacity,collisions\n";
    exp_file.close();

    create_file_with_directory(probab_path);
    ofstream prob_file(probab_path);
    if (!prob_file.is_open()) {
        throw std::invalid_argument("Unrorrect file_path!");
    }
    prob_file << "table_capacity,probability[at least 1 collision]\n";
    prob_file.close();


    for (int table_cap = 25; table_cap <= 475; table_cap += 50) {
        sub_experiment(table_cap, experiments_path, probab_path, group_count);
    }
}


bool write_exp_results(Experiment exp, const std::string& filepath) {
    ofstream file(filepath, std::ios::app);
    if (!file.is_open()) {
        throw std::invalid_argument("File does not exist!");
    }
    
    file << exp.table_start_capacity << "," << exp.collisions << '\n';
}

bool write_probability(const int table_cap, const double p, const std::string& filepath) {
    ofstream file(filepath, std::ios::app);
    if (!file.is_open()) {
        throw std::invalid_argument("File does not exist!");
    }

    file << table_cap << "," << p << '\n';
}