#pragma once

#include <vector>

class Map;
class GBFile;

class MapTree {
public:
    static void genMapTree(std::vector<GBFile>& gbFiles);
private:
    MapTree();
};