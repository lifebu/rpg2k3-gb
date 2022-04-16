#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"


int main (int argc, char* argv[]) {
    CLIOptions cli = CLIOptions(argc, argv);
    if(cli.printErrors()) return 0;
    if(cli.printInfo()) return 0;

    std::vector<GBFile> gbFiles = GBFile::genGBFiles(cli);

    int numOfMaps = Map::genMapFiles(gbFiles);

    MapTree::genMapTree(numOfMaps);

    Database::genDatabase(gbFiles);

    genProjectFolder(numOfMaps);

    return 0;
}