#include <string>
#include <cmath>

namespace CLI {
    const static std::string VERSION_STRING = "0.1\n";
    const static std::string HELP_STRING = "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom\n" 
                                    "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN]\n"
                                    "          --help/-h: print help\n"
                                    "          --version/-v: print version information\n"
                                    "          --gb/-g: list of Gameboy roms to load\n";
};

namespace FOLDERS {
    const static std::string TEMPLATE_PATH = "rpg2k3/templates/";
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


    // Map-Event Offsets:
    // DMG Event has always the first ID.
    const static int DMG_EVENT_ID = 1;
    // MAP ROM Events start with 2nd ID.
    const static int MAP_ROM_ID = 2;
};

namespace RPGMAKER {
    // If I use the Value Bias.
    const static bool USE_RPG_VALUE_BIAS = false;
    // Check if disabling the value_bias creates an overflow:
    static_assert(USE_RPG_VALUE_BIAS == false && MEMORYSIZE::BYTES_PER_VAR < 3, 
    "USE_RPG_VALUE_BIAS is disabled, but when using 3 Bytes per Var, the Bias is needed to avoid overflow in RPG Maker.");
    // int32_t to RPG Maker Value Bias. I want a symmetrical value range in RPG Maker. 
    // e.g. MEMORYSIZE::BYTES_PER_VAR = 3 =>
    // 2^24 = ceil((16.777.216) / 2) = 8.388.608 => RPG Maker: [-8.338.608, 8.338.607]
    const static uint32_t RPG_VALUE_BIAS = pow(2, MEMORYSIZE::BYTES_PER_VAR*8) / 2;

    // Map
    const static int MAP_SIZE_X = 500;
    const static int MAP_SIZE_Y = 500;

    // TODO: Need a better representation for Variable IDs, but good enough for now.
    // Variables
    const static int BYTE_OFFSET_ID = 1;
    const static int LABEL_ID = 2;
    const static int READ_VAR_1 = 3;
    const static int READ_VAR_2 = 4;
};
