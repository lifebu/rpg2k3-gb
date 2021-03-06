#include "CLI.h"

#include <iostream>
#include <algorithm>

using namespace gb2rpg;

const static std::string VERSION_STRING = "0.1\n";
const static std::string HELP_STRING =  "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom\n" 
                                        "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN]\n"
                                        "      --help/-h: print help\n"
                                        "      --version/-v: print version information\n"
                                        "      --gb/-g: list of Gameboy roms to load\n";


const static std::string ERR_TO_MANY_GB_FILES = "For memory reasons, GB2RPG currently can only support the generation of one mapfile at a time.\n";

CLIOptions::CLIOptions(int argc, char* argv[])
    : printVersion(false), printHelp(false), filePaths() {
    parseArguments(argc, argv);

    if(filePaths.size() > 1) {std::cout << ERR_TO_MANY_GB_FILES; error = true;}
    if(printVersion) std::cout << VERSION_STRING;
    if(printHelp || (!printHelp && !printVersion && filePaths.empty())) std::cout << HELP_STRING;

}


bool CLIOptions::shouldEnd() {
    if(printVersion || printHelp || filePaths.empty()) return true;
    return error;
}

std::vector<std::string>& CLIOptions::getFilePaths() {
    return filePaths;
}

/*
* Returns index of the last parameter that still belongs to the argument which starts at start.
*/
int CLIOptions::findParameterRange(int argc, char* argv[], int start) {
    int i = start + 1;
    for(; i < argc; ++i) {
        std::string nextArgument = argv[i];
        if (nextArgument.find("-") != std::string::npos 
            || nextArgument.find("--") != std::string::npos) {
            break;
        }
    }
    return i - 1;
}

/*
* sanitizes command line inputs for paths
*/
void CLIOptions::sanitizePath(std::string& path) {
    path.erase(remove(path.begin(), path.end(), '\\'), path.end());
}

void CLIOptions::parseArguments(int argc, char* argv[]) {
    // first argument always program path and name, so ignore it.
    for (int i = 1; i < argc; ++i) {
        std::string argument = argv[i];
        if (argument == "-v" || argument == "--version") {
            printVersion = true;
        
        } else if (argument == "-h" || argument == "--help") {
            printHelp = true;
        
        } else if (argument == "-g" || argument == "--gb") {
            int last = findParameterRange(argc, argv, i);
            int numParams = last - i;
            filePaths.reserve(numParams);

            for (int param = i + 1; param <= last; ++param) {
                std::string path = std::string(argv[param]);
                sanitizePath(path);
                filePaths.push_back(path);
            }
        
        }
    }
}