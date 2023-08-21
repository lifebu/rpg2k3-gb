#pragma once

#include <string>

namespace GLOBALS
{

namespace PROJECT 
{
    // Folders:
    const static std::string TEMPLATE_DIR = "data/templates/project/";
    const static std::string PROJECT_DIR = "project/";
    const static std::string RPG_PROJECT_DIR = "project/rpg2k3/";

    // Input files giving the switches and variables names.
    const static std::string VAR_NAMES = "var_names.txt";
    const static std::string SWITCH_NAMES = "switch_names.txt";

    // Commonevent File that will come from the compiler.
    const static std::string COMMON_EVENTS = "common_events.xml";

    // Proprietary RPG Maker Files
    const static std::string RPGMAKER_PRJ_FILE = "Gameboy_Emulator.r3proj";
    const static std::string RPGMAKER_INI_FILE = "RPG_RT.ini";
    const static std::string REQUIRED_RPGMAKER_FILES[] = {
        "RPG_RT.exe",
        "ultimate_rt_eb.dll"
    };

    // Folders to generate
    const static std::string DIRECTORIES[] = {
        "project/rpg2k3/Backdrop",
        "project/rpg2k3/Battle",
        "project/rpg2k3/Battle2",
        "project/rpg2k3/BattleCharSet",
        "project/rpg2k3/BattleWeapon",
        "project/rpg2k3/CharSet",
        "project/rpg2k3/ChipSet",
        "project/rpg2k3/FaceSet",
        "project/rpg2k3/Frame",
        "project/rpg2k3/GameOver",
        "project/rpg2k3/Monster",
        "project/rpg2k3/Movie",
        "project/rpg2k3/Music",
        "project/rpg2k3/Panorama",
        "project/rpg2k3/Picture",
        "project/rpg2k3/Sound",
        "project/rpg2k3/System",
        "project/rpg2k3/System2",
        "project/rpg2k3/Title"
    };
};

namespace EXPORTS 
{
    // Map
    const static std::string MAP_FILE_BASE = "Map";
    const static std::string MAP_FILE_TYPE = ".emu";

    // Maptree
    const static std::string MAPTREE_FILE = "RPG_RT.emt";

    // Database
    const static std::string DATABASE_FILE = "RPG_RT.edb";
};  

}