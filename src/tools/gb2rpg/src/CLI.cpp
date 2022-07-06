#include "CLI.h"

#include <iostream>
#include <algorithm>

using namespace std;

const static std::string VERSION_STRING = "0.1\n";
const static std::string HELP_STRING =  "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom\n" 
                                        "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN] [-o: cpp_rpg_env/easy_rpg/rpg_maker_2k3]\n"
                                        "      --help/-h: print help\n"
                                        "      --version/-v: print version information\n"
                                        "      --gb/-g: list of Gameboy roms to load\n"
                                        "      -o: what kind project to create:\n"
                                        "            cpp_rpg_env: Create a project for included C++ environment\n"
                                        "            easy_rpg: Create a project for the EasyRPG player\n"
                                        "            rpg_maker_2k3: Create a project for the RPG Maker 2003\n";


const static std::string ERR_TO_MANY_GB_FILES = "For memory reasons, GB2RPG currently can only support the generation of one mapfile at a time.\n";
const static std::string ERR_INVALID_PROJECT_TYPE = "Error: unknown or unsupplied project type using the -o argument, use -o with 'cpp_rpg_env', 'easy_rpg' or 'rpg_maker_2k3'. \n";

CLIOptions::CLIOptions(int argc, char* argv[])
    : printVersion(false), printHelp(false), filePaths(), projectType(INVALID) {
    parseArguments(argc, argv);
}

/*
* true = help or version mode.
*/
bool CLIOptions::printInfo() {
    if(!printVersion && !printHelp && !filePaths.empty()) return false;
    if(printVersion) {
        cout << VERSION_STRING;
    } 
    if (printHelp || (!printHelp && !printVersion && filePaths.empty())) {
        cout << HELP_STRING;
    }

    return true;
}
bool CLIOptions::printErrors() {
    if(filePaths.size() > 1) {
        // for Memory Reasons we only support one .gb file right now.
        cout << ERR_TO_MANY_GB_FILES;
        return true;
    }

    if(projectType == INVALID) {
        cout << ERR_INVALID_PROJECT_TYPE;
        return true;
    }

    return false;
}

std::vector<std::string>& CLIOptions::getFilePaths() {
    return filePaths;
}

CLIOptions::ProjectType CLIOptions::getProjectType() {
    return projectType;
}

/*
* Returns index of the last parameter that still belongs to the argument which starts at start.
*/
int CLIOptions::findParameterRange(int argc, char* argv[], int start) {
    int i = start + 1;
    for(; i < argc; ++i) {
        string nextArgument = argv[i];
        if (nextArgument.find("-") != string::npos 
            || nextArgument.find("--") != string::npos) {
            break;
        }
    }
    return i - 1;
}

/*
* sanitizes command line inputs for paths
*/
void CLIOptions::sanitizePath(string& path) {
    path.erase(remove(path.begin(), path.end(), '\\'), path.end());
}

void CLIOptions::parseArguments(int argc, char* argv[]) {
    // first argument always program path and name, so igore it.
    for (int i = 1; i < argc; ++i) {
        string argument = argv[i];
        if (argument == "-v" || argument == "--version") {
            printVersion = true;
        
        } else if (argument == "-h" || argument == "--help") {
            printHelp = true;
        
        } else if (argument == "-g" || argument == "--gb") {
            int last = findParameterRange(argc, argv, i);
            int numParams = last - i;
            filePaths.reserve(numParams);

            for (int param = i + 1; param <= last; ++param) {
                string path = string(argv[param]);
                sanitizePath(path);
                filePaths.push_back(path);
            }
        
        } else if (argument == "-o") {
            string parameter = argv[i + 1];
            // TODO: Maybe there is a more elegent solution than this?
            if (parameter.find("cpp_rpg_env") != std::string::npos) {
                projectType = CPP_RPG_ENV;
            } else if (parameter.find("easy_rpg") != std::string::npos) {
                projectType = EASY_RPG;
            } else if (parameter.find("rpg_maker_2k3") != std::string::npos) {
                projectType = RPG_MAKER_2K3;
            } else {
                // This is an error case, you need to supply a project type.
                projectType = INVALID;
            }
        }
    }
}