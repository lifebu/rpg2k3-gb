#pragma once

#include "../lcf/Map.h"

#include <string>


namespace lcf {

class MapSerializer {

public:
    MapSerializer() = delete;

    static Map FromFile(std::string fileName);
    static void ToFile(std::string fileName, Map& map);
};

};