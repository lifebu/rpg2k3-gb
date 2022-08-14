#pragma once

#include "../lcf/Database.h"

#include <string>


namespace lcf {

class DatabaseSerializer {

public:
    DatabaseSerializer() = delete;

    static Database FromFile(std::string fileName);
    static void ToFile(std::string fileName, Database& database);
};

};