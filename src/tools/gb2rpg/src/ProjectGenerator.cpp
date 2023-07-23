#include "ProjectGenerator.h"

#include "Globals.h"

#include "core/def/Globals.h"
#include "core/utilities/RPGHelper.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace gb2rpg;

const static std::string ERR_LCF = "Error: Could not create one of the binary files using lcf2xml, do 3 files exist in the project/ folder?\n";
const static std::string ERR_PROPRIETARY = "Error: Could not find proprietary RPG Maker file in " + GLOBALS::PROJECT::TEMPLATE_DIR + ": ";
const static std::string WARN_PROPRIETARY = "Info: At least one proprietary RPG Maker file not found. Create a new project in RPG Maker 2003 called 'Gameboy_Emulator' and copy the missing files to " + GLOBALS::PROJECT::TEMPLATE_DIR + ".";

// public
void ProjectGenerator::cleanProjectFolder() 
{
    std::cout << "Cleaning/Creating project folder: project/\n";
    try 
    {
        fs::remove_all(GLOBALS::PROJECT::PROJECT_DIR);  
        fs::create_directories(GLOBALS::PROJECT::RPG_PROJECT_DIR);
        fs::copy("easyrpg-player", GLOBALS::PROJECT::RPG_PROJECT_DIR);

    } catch (fs::filesystem_error err) 
    {
        std::cout << err.what() << std::endl;
    }
}

void ProjectGenerator::genProjectFolder(int numOfMaps) 
{
    std::cout << "Creating project folder: project/rpg2k3\n";
    createProjectData(numOfMaps);
    genFolders();
}

// private
void ProjectGenerator::createProjectData(int numOfMaps) 
{
    // create the binary files
    auto currentPath = fs::current_path();
    fs::current_path(GLOBALS::PROJECT::RPG_PROJECT_DIR);

    int ret;
    std::cout << "Converting database to: RPG_RT.ldb\n";
    ret = system(std::string("./../../lcf2xml ../" + GLOBALS::EXPORTS::DATABASE_FILE).c_str());
    std::cout << "Converting map tree to: RPG_RT.lmt\n";
    ret = system(std::string("./../../lcf2xml ../" + GLOBALS::EXPORTS::MAPTREE_FILE).c_str());
    for(int mapID = 1; mapID <= numOfMaps; ++mapID) 
    {
        std::string mapName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(mapID) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
        std::cout << "Converting map to: " << mapName << std::endl;
        std::string mapFile = "./../../lcf2xml ../" + mapName;
        ret = system(mapFile.c_str());
    }
    if(ret) std::cout << ERR_LCF;

    fs::current_path(currentPath);
    
    // copy proprietary data from templates/project to project/rpg2k3
    bool oneProprietaryNotFound = false;
    for (auto& rpgFile : GLOBALS::PROJECT::RPGMAKER_FILES) {
        try 
        {
            fs::copy(GLOBALS::PROJECT::TEMPLATE_DIR + rpgFile, GLOBALS::PROJECT::RPG_PROJECT_DIR + rpgFile);
        } catch(fs::filesystem_error err) {
            std::cout << ERR_PROPRIETARY << rpgFile << std::endl;
            oneProprietaryNotFound = true;
        }
    }

    if(oneProprietaryNotFound) {
        std::cout << WARN_PROPRIETARY << std::endl;
    }
}

void ProjectGenerator::genFolders() 
{
    try 
    {
        for (auto& dir : GLOBALS::PROJECT::DIRECTORIES) 
        {
            fs::create_directories(dir);
        }
    
    } catch(fs::filesystem_error err) 
    {
        std::cout << err.what() << std::endl;
    }
}