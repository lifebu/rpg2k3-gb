#include <string>
#include <cmath>

namespace TEMPLATES {
    // TODO: Can I do static_asserts to ensure that the files exist?
    // database
    const static char* CHARACTER = "rpg2k3/templates/database/character.xml";
    const static char* COMMON_EVENT = "rpg2k3/templates/database/common_event.xml";
    const static char* DATABASE = "rpg2k3/templates/database/database.xml";
    const static char* ITEM = "rpg2k3/templates/database/item.xml";
    const static char* SWITCH = "rpg2k3/templates/database/switch.xml";
    const static char* VARIABLE = "rpg2k3/templates/database/variable.xml";

    // event
    const static char* EVENT_COMMAND = "rpg2k3/templates/event/event_command.xml";
    const static char* EVENT_PAGE = "rpg2k3/templates/event/event_page.xml";
    const static char* EVENT = "rpg2k3/templates/event/event.xml";

    // map
    const static char* MAP = "rpg2k3/templates/map/map.xml";
    const static char* MAP_INFO = "rpg2k3/templates/map/map_info.xml";
    const static char* MAP_TREE = "rpg2k3/templates/map/map_tree.xml";

    // general
    const static char* DMG_ROM = "rpg2k3/templates/dmg_rom.xml";
    const static char* MAP_ROM_HEADER = "rpg2k3/templates/map_rom_header.xml";
    const static char* MAP_ROM_LABEL = "rpg2k3/templates/map_rom_label.xml";
};

namespace EXPORTS {
    // Map
    const static std::string MAP_BASE = "rpg2k3/project/Map";
    const static std::string MAP_TYPE = ".emu";

    // Maptree
    const static std::string MAP_TREE = "rpg2k3/project/RPG_RT.emt";
};