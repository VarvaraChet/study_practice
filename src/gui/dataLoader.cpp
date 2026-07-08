#include "dataLoader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector <Task> DataLoader::load(const std::string& filename){
    std::vector <Task> tasks;
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Не удалось открыть файл");

    std::string line;
    int id=1;

    while (std::getline(file, line)){
        if (line.empty())
            continue;

        std::stringstream ss(line);

        int time;
        int deadline;

        ss >> time >> deadline;

        if (ss.fail())
            throw std::runtime_error("Ошибка чтения строки файла");

        Task task;
        task.id = id++;
        task.time = time;
        task.deadline = deadline;

        tasks.push_back(task);
    }

    return tasks;
}
