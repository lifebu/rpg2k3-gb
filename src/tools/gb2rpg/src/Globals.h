#include <string>

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
    // Var € [-9.999.999, 9.999.999] = 20Mio_10 >= 16.777.216_10 = 2^24 = 3 Bytes
    const static int BYTES_PER_VAR = 3;
    // GB Ops Read/Write [1,2] Bytes. 
    // If address falls onto last byte of one Var, I need the next Var. 
    // Therefore always return 2 Vars (6 Byte).
    const static int VARS_PER_READWRITE = 2;
    // Maximum number of labels possible per event page.
    const static int MAX_LABELS_PER_EPAGE = 1000; 
    // TODO: need to test which VARS_PER_EPAGE gives best performance! 
    // How many Variables one event page is responsible for. Range: [VARS_PER_READWRITE, MAX_LABELS_PER_EPAGE].
    // Increasing this makes event-page code more complex, requires less event-pages in total.
    // Decreaing this makes event-pages code simpler, but we require more event-pages in total.
    const static int VARS_PER_EPAGE = 1000;
    static_assert(VARS_PER_READWRITE <= VARS_PER_EPAGE && VARS_PER_EPAGE <= MAX_LABELS_PER_EPAGE, 
    "VARS_PER_EPAGE needs to be in Range [VARS_PER_READWRITE, MAX_LABELS_PER_EPAGE]");
    // How many Bytes one event-page is responsible for. This is needed for converting Gameboy Addresses to EventIDs and Per Event-Page ByteOffsets.
    const static int BYTES_PER_EPAGE = VARS_PER_EPAGE * BYTES_PER_VAR;


    // Map-Event Offsets:
    // DMG Event has always the first ID.
    const static int DMG_EVENT_ID = 1;
    // MAP ROM Events start with 2nd ID.
    const static int MAP_ROM_ID = 2;
};