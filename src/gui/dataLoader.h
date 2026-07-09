#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include <string>

#include "../algorithm/task.h"

class DataLoader{
    public:
        bool load(const std::string& filename, std::vector <Task>& tasks);
};

#endif
