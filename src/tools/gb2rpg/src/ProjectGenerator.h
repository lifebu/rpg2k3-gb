#pragma once

#include <vector>

class GBFile;

class ProjectGenerator {
public:
    static void genProjectFolder(std::vector<GBFile>& gbFiles);
};
