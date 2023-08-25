#include "ProjectGenerator.h"

#include <fstream>
#include <string>
#include <filesystem>

#include <core/def/Globals.h>
#include <core/utilities/RPGHelper.h>
#include <core/structure/Logger.h>

#include "gb2rpg/def/Globals.h"

namespace fs = std::filesystem;
using namespace gb2rpg;

const static std::string ERR_LCF = "Could not create one of the binary files using lcf2xml, do 3 files exist in the project/ folder?";
const static std::string ERR_PROPRIETARY = "Could not find proprietary RPG Maker file in " + GLOBALS::PROJECT::TEMPLATE_DIR + ": ";
const static std::string INFO_PROPRIETARY = "At least one proprietary RPG Maker file not found. Create a new project in RPG Maker 2003 and copy the missing files to " + GLOBALS::PROJECT::TEMPLATE_DIR + ".";
const static std::string ERR_GEN_PROJ_FILE = "Could not create RPG Maker project file";
const static std::string ERR_GEN_INI_FILE = "Could not create RPG Maker ini file";

// public
void ProjectGenerator::cleanProjectFolder() 
{
    core::Logger::Get()->Log("Cleaning/Creating project folder: project/", core::LogLevel::INFO);
    try 
    {
        fs::remove_all(GLOBALS::PROJECT::PROJECT_DIR);  
        fs::create_directories(GLOBALS::PROJECT::RPG_PROJECT_DIR);
        fs::copy("easyrpg-player", GLOBALS::PROJECT::RPG_PROJECT_DIR);

    } catch (fs::filesystem_error err) 
    {
        core::Logger::Get()->Log(err.what(), core::LogLevel::ERROR);
    }
}

void ProjectGenerator::genProjectFolder(int numOfMaps) 
{
    core::Logger::Get()->Log("Creating project folder: project/rpg2k3", core::LogLevel::INFO);
    createProjectData(numOfMaps);
    genFolders();
}

// private
void ProjectGenerator::createProjectData(int numOfMaps) 
{
    core::Logger* const logger = core::Logger::Get();

    // create the binary files
    auto currentPath = fs::current_path();
    fs::current_path(GLOBALS::PROJECT::RPG_PROJECT_DIR);

    int ret;
    logger->Log("Converting database to: RPG_RT.ldb", core::LogLevel::INFO);
    ret = system(std::string("./../../lcf2xml ../" + GLOBALS::EXPORTS::DATABASE_FILE).c_str());
    logger->Log("Converting map tree to: RPG_RT.lmt", core::LogLevel::INFO);
    ret = system(std::string("./../../lcf2xml ../" + GLOBALS::EXPORTS::MAPTREE_FILE).c_str());
    for(int mapID = 1; mapID <= numOfMaps; ++mapID) 
    {
        std::string mapName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(mapID) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
        logger->Log("Converting map to: " + mapName, core::LogLevel::INFO);
        std::string mapFile = "./../../lcf2xml ../" + mapName;
        ret = system(mapFile.c_str());
    }
    if(ret) logger->Log(ERR_LCF, core::LogLevel::ERROR);

    fs::current_path(currentPath);

    // generate config files
    genRPGProjFile();
    genRPGIniFile();
    
    // copy proprietary data from data/templates/project to project/rpg2k3
    bool oneProprietaryNotFound = false;
    for (auto& rpgFile : GLOBALS::PROJECT::REQUIRED_RPGMAKER_FILES) {
        try 
        {
            fs::copy(GLOBALS::PROJECT::TEMPLATE_DIR + rpgFile, GLOBALS::PROJECT::RPG_PROJECT_DIR + rpgFile);
        } catch(fs::filesystem_error err) {
            logger->Log(ERR_PROPRIETARY + rpgFile, core::LogLevel::ERROR);
            oneProprietaryNotFound = true;
        }
    }

    if(oneProprietaryNotFound) {
        logger->Log(INFO_PROPRIETARY, core::LogLevel::INFO);
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
        core::Logger::Get()->Log(err.what(), core::LogLevel::ERROR);
    }
}

void gb2rpg::ProjectGenerator::genRPGProjFile() 
{
    core::Logger* const logger = core::Logger::Get();
    logger->Log("Generating project file " + GLOBALS::PROJECT::RPGMAKER_PRJ_FILE + ".", core::LogLevel::INFO);

    std::ofstream projFile(GLOBALS::PROJECT::RPG_PROJECT_DIR + GLOBALS::PROJECT::RPGMAKER_PRJ_FILE);
    if(!projFile.is_open())
    {
        logger->Log(ERR_GEN_PROJ_FILE, core::LogLevel::ERROR);
        return;
    }

    projFile << "RPG2003 v1.12a" << std::endl;
    projFile.close();
}

void gb2rpg::ProjectGenerator::genRPGIniFile() 
{
    core::Logger* const logger = core::Logger::Get();
    logger->Log("Generating ini file " + GLOBALS::PROJECT::RPGMAKER_INI_FILE + ".", core::LogLevel::INFO);

    std::ofstream iniFile(GLOBALS::PROJECT::RPG_PROJECT_DIR + GLOBALS::PROJECT::RPGMAKER_INI_FILE);
    if(!iniFile.is_open())
    {
        logger->Log(ERR_GEN_INI_FILE, core::LogLevel::ERROR);
        return;
    }

    iniFile << "[RPG_RT]" << std::endl
            << "GameTitle=Gameboy_Emulator" << std::endl
            << "MapEditMode=0" << std::endl
            << "MapEditZoom=0" << std::endl;

    iniFile.close();
}
