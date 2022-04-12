#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"


int main (int argc, char* argv[]) {
    CLIOptions cli = CLIOptions(argc, argv);
    if(cli.printInfo()) return 0;

    std::vector<GBFile> gbFiles = GBFile::genGBFiles(cli);

    std::vector<Map> maps = Map::genMapFiles(gbFiles);

    MapTree mapTree = MapTree(maps);

    Database database = Database(gbFiles);    

    genProjectFolder(maps, mapTree, database);

    return 0;
}