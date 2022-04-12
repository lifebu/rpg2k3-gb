#include<vector>
#include<string>

class CLIOptions {
public:
    CLIOptions(int argc, char* argv[]);

    bool printInfo();

    std::vector<std::string>& getFilePaths();

private:
    void parseArguments(int argc, char* argv[]);

    std::vector<std::string> filePaths;
    bool printVersion;
    bool printHelp;
};
