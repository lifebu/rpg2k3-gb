#pragma once

#include <vector>
#include <string>

namespace gb2rpg {
    class CLIOptions {
    public:
        CLIOptions(int argc, char* argv[]);

        bool shouldEnd();

        std::vector<std::string>& getFilePaths();

    private:
        int findParameterRange(int argc, char* argv[], int start);
        void sanitizePath(std::string& path);
        void parseArguments(int argc, char* argv[]);

        bool printVersion;
        bool printHelp;
        bool error;

        std::vector<std::string> filePaths;
    };
};
