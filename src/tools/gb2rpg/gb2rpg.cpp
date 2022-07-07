#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"


int main (int argc, char* argv[]) {
    // TODO: Should find a cleaner way for printing errors and printing the info CLI-info string in main.
    CLIOptions cli = CLIOptions(argc, argv);
    if(cli.printErrors()) return 0;
    if(cli.printInfo()) return 0;

    GBFileGenerator gbGen;
    std::vector<GBFile> gbFiles = gbGen.genGBFiles(cli);
    if(gbGen.hadErrors()) return 0;

    int numOfMaps = Map::genMapFiles(gbFiles);

    MapTree::genMapTree(gbFiles);

    Database::genDatabase(gbFiles);

    genProjectFolder(numOfMaps, cli);

    return 0;
}