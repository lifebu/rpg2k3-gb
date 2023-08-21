#pragma once

#include <vector>


namespace gb2rpg {
    class Map;
    class GBFile;


    class MapTree {
    public:
        MapTree() = delete;

        static void genMapTree(std::vector<GBFile>& gbFiles);
    };
};