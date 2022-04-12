#include <string>

namespace CLI {
    static std::string versionString = "0.1\n";
    static std::string helpString = "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom\n" 
                                    "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN]\n"
                                    "          --help/-h: print help\n"
                                    "          --version/-v: print version information\n"
                                    "          --gb/-g: list of Gameboy roms to load\n";
};

namespace FOLDERS {
    static std::string templatePath = "rpg2k3/templates/";
};
