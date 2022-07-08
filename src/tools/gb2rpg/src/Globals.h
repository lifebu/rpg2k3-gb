#include <string>
#include <cmath>

#include "src/core/utilities/RPGHelper.h"

namespace TEMPLATES {
    // TODO: Can I do static_asserts to ensure that the files exist?
    // database
    const static char* CHARACTER = "templates/database/character.xml";
    const static char* COMMON_EVENT = "templates/database/common_event.xml";
    const static char* DATABASE = "templates/database/database.xml";
    const static char* ITEM = "templates/database/item.xml";
    const static char* SWITCH = "templates/database/switch.xml";
    const static char* VARIABLE = "templates/database/variable.xml";

    // event
    const static char* EVENT_COMMAND = "templates/event/event_command.xml";
    const static char* EVENT_PAGE = "templates/event/event_page.xml";
    const static char* EVENT = "templates/event/event.xml";

    // map
    const static char* MAP = "templates/map/map.xml";

    // map tree
    const static char* MAP_TREE = "templates/map/map_tree.xml";
    const static char* MAP_INFO = "templates/map/map_info.xml";

    // general
    const static char* DMG_ROM = "templates/dmg_rom.xml";
    const static char* MAP_ROM_HEADER = "templates/map_rom_header.xml";
    const static char* MAP_ROM_LABEL = "templates/map_rom_label.xml";
};

namespace EXPORTS {
    // Map
    const static std::string MAP_FILE_BASE = "Map";
    const static std::string MAP_FILE_TYPE = ".emu";

    // Maptree
    const static std::string MAPTREE_FILE = "RPG_RT.emt";

    // Database
    const static std::string DATABASE_FILE = "RPG_RT.edb";
};

namespace PROJECT {
    const static std::string TEMPLATE_DIR = "templates/project/";
    const static std::string PROJECT_DIR = "project/";
    const static std::string RPG_PROJECT_DIR = "project/rpg2k3/";

    // Proprietary RPG Maker Files
    const static std::string RPGMAKER_FILES[] = {
        "Gameboy_Emulator.r3proj",
        "RPG_RT.exe",
        "RPG_RT.ini",
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