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
};

namespace MEMORYSIZE {
    // Gameboy Memory Sizes:
    // (Byte), 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register
    const static int DMG_RAM_SIZE = 16800;
    // (Byte), How much cartridge RAM we can support (64kB and 128kB are possible for a cartridge, but not supported).
    static int MAX_CARTRIDGE_RAM = 32768;

    // Map-RAM:
    // map-size = 500x500 = 250000_10 >= 131072_10 = 2^17
    const static int BITS_PER_EVENT_POS = 17;
    // 7906 Events needed.
    const static int NUM_DMG_RAM_EVENTS = (DMG_RAM_SIZE * 8) / BITS_PER_EVENT_POS + 1;


    // Map-ROM:
    // How many pages one Event can have
    const static int MAX_PAGES_PER_EVENT = 100;
    // TODO: which BYTES_PER_VAR values is best?
    // BYTES_PER_VAR € [1,3], because:
    // Var € [-9.999.999, 9.999.999] = 20Mio_10 >= 16.777.216_10 = 2^24 = 3 Bytes
    const static int BYTES_PER_VAR = 1;
    static_assert(1 <= BYTES_PER_VAR && BYTES_PER_VAR <= 3, 
    "BYTES_PER_VAR needs to be in Range [1, 3]");
    // GB Ops Read/Write [1,2] Bytes. 
    // If address falls onto last byte of one Var, I need the next Var. 
    // Therefore always return 2 Vars (6 Byte).
    const static int VARS_PER_READWRITE = 2;
    // Maximum number of labels possible per event page.
    const static int MAX_LABELS_PER_EPAGE = 1000; 
    // TODO: need to test which VARS_PER_EPAGE gives best performance! 
    // How many Variables one event page is responsible for. Range: [1, MAX_LABELS_PER_EPAGE].
    // Increasing this makes event-page code more complex, requires less event-pages in total.
    // Decreaing this makes event-pages code simpler, but we require more event-pages in total.
    const static int VARS_PER_EPAGE = 1000;
    static_assert(1 <= VARS_PER_EPAGE && VARS_PER_EPAGE <= MAX_LABELS_PER_EPAGE, 
    "VARS_PER_EPAGE needs to be in Range [VARS_PER_READWRITE, MAX_LABELS_PER_EPAGE]");
    // How many Bytes one event-page is responsible for. This is needed for converting Gameboy Addresses to EventIDs and Per Event-Page ByteOffsets.
    const static int BYTES_PER_EPAGE = VARS_PER_EPAGE * BYTES_PER_VAR;
};

namespace RPGMAKER {
    // If I use the Value Bias.
    const static bool USE_RPG_VALUE_BIAS = false;
    // Check if disabling the value_bias creates an overflow:
    static_assert(USE_RPG_VALUE_BIAS == false && MEMORYSIZE::BYTES_PER_VAR < 3 || USE_RPG_VALUE_BIAS == true, 
    "USE_RPG_VALUE_BIAS is disabled, but when using 3 Bytes per Var, the Bias is needed to avoid overflow in RPG Maker.");
    // int32_t to RPG Maker Value Bias. I want a symmetrical value range in RPG Maker. 
    // e.g. MEMORYSIZE::BYTES_PER_VAR = 3 =>
    // 2^24 = ceil((16.777.216) / 2) = 8.388.608 => RPG Maker: [-8.338.608, 8.338.607]
    const static uint32_t RPG_VALUE_BIAS = pow(2, MEMORYSIZE::BYTES_PER_VAR*8) / 2;

    // Map
    const static int MAP_SIZE_X = 500;
    const static int MAP_SIZE_Y = 500;
};

namespace VARMAPPING {
    const static int BYTE_OFFSET_ID = 1;
    const static int LABEL_ID = 2;
    const static int READ_VAR_1 = 3;
    // Second Variable is overhead for the case that a 2-Byte R/W Op needs the last Byte of the first Var and the next byte.
    const static int READ_VAR_2 = 4;
};