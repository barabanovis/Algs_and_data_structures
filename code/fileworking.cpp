#include "fileworking.h"
#include "UnorderedMap.h"

using namespace std;

namespace fs = std::filesystem;

bool create_file_with_directory(const std::string& filepath) {
    try {
        // �������� ���� � ���������� �� ������� ���� � �����
        fs::path directory = fs::path(filepath).parent_path();

        // ������ ���������� (� ��� ������������, ���� �����), ���� � ���
        if (!directory.empty() && !fs::exists(directory)) {
            fs::create_directories(directory);
            std::cout << "Created directory: " << directory << std::endl;
        }

        // ������ ����
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
        std::cerr << "������ �������� �������: " << ex.what() << std::endl;
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

// ������ 100 ������� ��� ����������� ������� �������
void sub_experiment(const size_t table_capacity, const string& experiments_path, const string& probab_path,const size_t group_count) {
    int count = 0; // ������� ����� ��������, ��� �� ���� ��������

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

    // C������� ������ ��� ���������� �����������
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

// Placeholder for class demonstration. Replace with your actual demo code.
void run_class_demo() {
    std::cout << "\n=== Hash table class demonstration ===\n\n";

    // Демонстрация конструктора с заполнением
    std::cout << "1. Creating a hash table with capacity 10, filling 8 slots with value 7.0:\n";
    UnorderedMap<float> my_map(10, 8, 7.0f);
    my_map.print();
    std::cout << "   Size: " << my_map.get_size() << ", Capacity: " << my_map.get_capacity();
    std::cout << ", Load factor: " << my_map.load_factor() << "\n\n";

    // Вставка нового элемента
    std::cout << "2. Inserting new element (35, 55.0):\n";
    bool insert_success = my_map.insert(35, 55.0f);
    if (insert_success) {
        std::cout << "   Insertion successful!\n";
    }
    else {
        std::cout << "   Insertion failed (key already exists or other issue).\n";
    }
    my_map.print();
    std::cout << "   Collisions count: " << my_map.count_collisions() << "\n\n";

    // Поиск элемента
    std::cout << "3. Searching for key 35:\n";
    float* found_value = my_map.search(35);
    if (found_value) {
        std::cout << "   Key 35 found, value: " << *found_value << "\n";
    }
    else {
        std::cout << "   Key 35 not found.\n";
    }

    // Проверка наличия значения (для float может быть не совсем корректно, но демонстрируем метод)
    std::cout << "4. Checking if value 55.0 exists in the map:\n";
    bool has_value = my_map.contains(55.0f);
    std::cout << "   Value 55.0 " << (has_value ? "found" : "not found") << "\n\n";

    // Подсчёт вхождений ключа
    std::cout << "5. Counting occurrences of key 35:\n";
    int key_count = my_map.count(35);
    std::cout << "   Key 35 appears " << key_count << " time(s)\n\n";

    // Обновление существующего элемента через insert_or_assign
    std::cout << "6. Using insert_or_assign to update key 35 with value 99.9:\n";
    my_map.insert_or_assign(35, 99.9f);
    my_map.print();

    // Повторный поиск обновлённого элемента
    found_value = my_map.search(35);
    if (found_value) {
        std::cout << "   Updated value for key 35: " << *found_value << "\n\n";
    }

    // Удаление элемента
    std::cout << "7. Erasing element with key 35:\n";
    bool erase_success = my_map.erase(35);
    if (erase_success) {
        std::cout << "   Element erased successfully!\n";
    }
    else {
        std::cout << "   Erase failed (key not found).\n";
    }
    my_map.print();
    std::cout << "   Current size: " << my_map.get_size() << "\n\n";

    // Демонстрация копирования
    std::cout << "8. Creating a copy of the current map using copy constructor:\n";
    UnorderedMap<float> copied_map(my_map);
    copied_map.print();

    // Демонстрация оператора присваивания
    std::cout << "9. Assigning copy to a new map using operator=:\n";
    UnorderedMap<float> assigned_map = copied_map;
    assigned_map.print();

    std::cout << "=== Demonstration completed ===\n";
}
