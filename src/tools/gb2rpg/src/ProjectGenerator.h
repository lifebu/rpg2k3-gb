#pragma once

#include <vector>

class GBFile;

class ProjectGenerator {
public:
    static void cleanProjectFolder();
    static void genProjectFolder(std::vector<GBFile>& gbFiles);

private:
    static void createProjectData(std::vector<GBFile>& gbFiles);
    static void genFolders();
};
