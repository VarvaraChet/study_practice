#include "dataLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

bool DataLoader::load(const std::string& filename, std::vector <Task>& tasks){
    std::ifstream file(filename);

    if (!file.is_open()){
        throw std::runtime_error("Не удалось открыть файл");
        return false;
    }

    std::string line;
    int id=1;

    while (std::getline(file, line)){
        if (line.empty())
            continue;

        std::stringstream ss(line);

        int time;
        int deadline;

        ss >> time >> deadline;

        if (ss.fail()){
            throw std::runtime_error("Ошибка чтения строки файла");
            return false;
        }

        Task task;
        task.time = time;
        task.deadline = deadline;

        tasks.push_back(task);
    }

    return true;
}
