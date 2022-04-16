#pragma once

#include <vector>
#include <string>

class CLIOptions {
public:
    CLIOptions(int argc, char* argv[]);

    bool printInfo();
    bool printErrors();

    std::vector<std::string>& getFilePaths();

private:
    int findParameterRange(int argc, char* argv[], int start);
    void sanitizePath(std::string& path);
    void parseArguments(int argc, char* argv[]);

    std::vector<std::string> filePaths;
    bool printVersion;
    bool printHelp;
};
