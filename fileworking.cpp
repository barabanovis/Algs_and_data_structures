#include "fileworking.h"

using namespace std;

namespace fs = std::filesystem;

bool create_file_with_directory(const std::string& filepath) {
    try {
        // Получаем путь к директории из полного пути к файлу
        fs::path directory = fs::path(filepath).parent_path();

        // Создаём директорию (и все родительские, если нужно), если её нет
        if (!directory.empty() && !fs::exists(directory)) {
            fs::create_directories(directory);
            std::cout << "Создана директория: " << directory << std::endl;
        }

        // Создаём файл
        std::ofstream file(filepath);
        if (!file) {
            std::cerr << "Ошибка: не удалось создать файл: " << filepath << std::endl;
            return false;
        }
        file.close();
        std::cout << "Файл создан: " << filepath << std::endl;
        return true;
    }
    catch (const fs::filesystem_error& ex) {
        std::cerr << "Ошибка файловой системы: " << ex.what() << std::endl;
        return false;
    }
}


//bool write_exp_results(const Experiment& exp, const std::string& filepath) {
//    ofstream file(filepath);
//    if (!file.is_open()) {
//        create_file_with_directory(filepath);
//    }
//    file(filepath);
//}