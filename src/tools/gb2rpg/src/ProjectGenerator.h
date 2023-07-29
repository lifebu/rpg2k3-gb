#pragma once

#include <vector>

namespace gb2rpg {
    class ProjectGenerator {
    public:
        static void cleanProjectFolder();
        static void genProjectFolder(int numOfMaps);

    private:
        static void createProjectData(int numOfMaps);
        static void genFolders();
        static void genRPGProjFile();
        static void genRPGIniFile();
    };
};
