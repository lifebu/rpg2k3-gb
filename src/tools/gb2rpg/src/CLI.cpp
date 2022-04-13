#include "CLI.h"

#include "Globals.h"

#include <iostream>
#include <algorithm>

using namespace std;

CLIOptions::CLIOptions(int argc, char* argv[])
    : printVersion(false), printHelp(false), filePaths() {
    parseArguments(argc, argv);
}

/*
* true = help or version mode.
*/
bool CLIOptions::printInfo() {
    if(!printVersion && !printHelp && !filePaths.empty()) return false;
    if(printVersion) {
        cout << CLI::VERSION_STRING;
    } 
    if (printHelp || (!printHelp && !printVersion && filePaths.empty())) {
        cout << CLI::HELP_STRING;
        //cout << "GB2RPG - Create RPG Maker 2003 Project Files from Gameboy Rom" << endl;
        //cout << "Usage: gb2rpg [--help/-h] [--version/-v] [-gb/-g] file1 [... fileN]" << endl;
        //cout << "          --help/-h: print help" << endl;
        //cout << "          --version/-v: print version information" << endl;
        //cout << "          --gb/-g: list of Gameboy roms to load" << endl;
    }

    return true;
}

std::vector<std::string>& CLIOptions::getFilePaths() {
    return filePaths;
}

/*
* Returns index of the last parameter that still belongs to the argument which starts at start.
*/
int findParameterRange(int argc, char* argv[], int start) {
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
void pathSanitize(string& path) {
    path.erase(remove(path.begin(), path.end(), '\\'), path.end());
}

void CLIOptions::parseArguments(int argc, char* argv[]) {
    // first argument always program path and name.
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
                pathSanitize(path);
                filePaths.push_back(path);
            }
        }
    }
}