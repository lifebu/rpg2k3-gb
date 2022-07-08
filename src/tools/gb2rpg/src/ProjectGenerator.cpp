#include "ProjectGenerator.h"

#include "GBFile.h"
#include "Globals.h"

#include "src/core/utilities/RPGHelper.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

const static std::string ERR_LCF = "Could not create one of the binary files using lcf2xml, do 3 files exist in the project/ folder?\n";

// public
void ProjectGenerator::cleanProjectFolder() {
    try {
        fs::remove_all(PROJECT::PROJECT_DIR);  
        fs::create_directories(PROJECT::RPG_PROJECT_DIR);
        fs::copy("lcf2xml", PROJECT::RPG_PROJECT_DIR);
        fs::copy("easyrpg-player", PROJECT::RPG_PROJECT_DIR);

    } catch (fs::filesystem_error err) {
        std::cout << err.what() << std::endl;
    }
}

void ProjectGenerator::genProjectFolder(std::vector<GBFile>& gbFiles) {
    createProjectData(gbFiles);
    genFolders();
}

// private
void ProjectGenerator::createProjectData(std::vector<GBFile>& gbFiles) {
    // create the binary files
    auto currentPath = fs::current_path();
    fs::current_path(PROJECT::RPG_PROJECT_DIR);

    int ret;
    ret = system(std::string("lcf2xml ../" + EXPORTS::DATABASE_FILE).c_str());
    ret = system(std::string("lcf2xml ../" + EXPORTS::MAPTREE_FILE).c_str());
    for(int mapID = 1; mapID <= gbFiles.size(); ++mapID) {
        std::string mapFile = "lcf2xml ../" + EXPORTS::MAP_FILE_BASE + generateID(mapID) + EXPORTS::MAP_FILE_TYPE;
        ret = system(mapFile.c_str());
    }
    if(ret) std::cout << ERR_LCF;

    fs::current_path(currentPath);
    


    // copy proprietary data from templates/project to project/rpg2k3
    try {
        for (auto& rpgFile : PROJECT::RPGMAKER_FILES) {
            fs::copy(PROJECT::TEMPLATE_DIR + rpgFile, PROJECT::RPG_PROJECT_DIR + rpgFile);
        }
    
    } catch(fs::filesystem_error err) {
        std::cout << err.what() << std::endl;
    }
}

void ProjectGenerator::genFolders() {
    try {
        for (auto& dir : PROJECT::DIRECTORIES) {
            fs::create_directories(dir);
        }
    
    } catch(fs::filesystem_error err) {
        std::cout << err.what() << std::endl;
    }
}