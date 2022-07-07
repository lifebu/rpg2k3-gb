#pragma once

#include <vector>

class Map;
class GBFile;

class MapTree {
public:
    MapTree() = delete;

    static void genMapTree(std::vector<GBFile>& gbFiles);
};