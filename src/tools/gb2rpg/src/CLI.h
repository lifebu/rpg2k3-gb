#pragma once

#include <vector>
#include <string>

class CLIOptions {
public:
    enum ProjectType {
        CPP_RPG_ENV,
        EASY_RPG,
        RPG_MAKER_2K3,
        INVALID
    };

    CLIOptions(int argc, char* argv[]);

    bool printInfo();
    bool printErrors();

    std::vector<std::string>& getFilePaths();
    ProjectType getProjectType();

private:
    int findParameterRange(int argc, char* argv[], int start);
    void sanitizePath(std::string& path);
    void parseArguments(int argc, char* argv[]);

    bool printVersion;
    bool printHelp;

    std::vector<std::string> filePaths;
    ProjectType projectType;
};
