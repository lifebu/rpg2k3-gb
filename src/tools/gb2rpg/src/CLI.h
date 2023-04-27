#pragma once

#include <vector>
#include <string>

namespace gb2rpg 
{

class CLIOptions 
{
public:
    enum class XMLParser
    {
        TINYXML,
        RAPIDXML
    };
public:
    CLIOptions(int argc, char* argv[]);

    bool shouldEnd();
    XMLParser getXMLParser();

    std::vector<std::string>& getFilePaths();

private:
    int findParameterRange(int argc, char* argv[], int start);
    void sanitizePath(std::string& path);
    void parseArguments(int argc, char* argv[]);

    bool printVersion;
    bool printHelp;
    bool error;
    XMLParser usedParser = XMLParser::TINYXML;

    std::vector<std::string> filePaths;
};

};
