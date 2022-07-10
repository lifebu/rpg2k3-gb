#pragma once

#include <vector>

class ProjectGenerator {
public:
    static void cleanProjectFolder();
    static void genProjectFolder(int numOfMaps);

private:
    static void createProjectData(int numOfMaps);
    static void genFolders();
};
