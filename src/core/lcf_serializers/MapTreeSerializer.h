#pragma once

#include "../lcf/MapTree.h"

#include <string>


namespace lcf {

class MapTreeSerializer {

public:
    MapTreeSerializer() = delete;

    static MapTree FromFile(std::string fileName);
    static void ToFile(std::string fileName, MapTree& mapTree);
};

};