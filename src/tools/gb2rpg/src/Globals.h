#include <string>
#include <cmath>

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
    const static char* MAP_BASE = "project/Map";
    const static char* MAP_TYPE = ".emu";

    // Maptree
    const static char* MAP_TREE = "project/RPG_RT.emt";

    // Database
    const static char* DATABASE = "project/RPG_RT.edb";
};