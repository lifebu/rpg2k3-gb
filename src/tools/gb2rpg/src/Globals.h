#include <string>

namespace CLI {
    static std::string VERSION_STRING = "0.1\n";
    static std::string HELP_STRING = "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom\n" 
                                    "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN]\n"
                                    "          --help/-h: print help\n"
                                    "          --version/-v: print version information\n"
                                    "          --gb/-g: list of Gameboy roms to load\n";
};

namespace FOLDERS {
    static std::string TEMPLATE_PATH = "rpg2k3/templates/";
};

namespace MEMORYSIZE {
    // (Byte), 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register
    static int DMG_RAM_SIZE = 16800;
    // (Byte), How much cartridge RAM we can support (64kB and 128kB are possible for a cartridge).
    static int MAX_CARTRIDGE_RAM = 32768;

    // map-size = 500x500 = 250000_10 >= 131072_10 = 2^17
    static int BITS_PER_EVENT_POS = 17;
    // 7906 Events needed.
    static int NUM_DMG_RAM_EVENTS = (DMG_RAM_SIZE * 8) / BITS_PER_EVENT_POS + 1;
};