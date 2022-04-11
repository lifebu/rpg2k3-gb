#include "CLI.h"

#include <string>

using namespace std;

CLIOptions::CLIOptions(int argc, char* argv[]) {
    string filePath = "data/Tetris.gb";
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "-f" && i + 1 <= argc) {
            filePath = argv[i + 1];
        }
    }
}