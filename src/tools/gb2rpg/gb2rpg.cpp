#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"


int main (int argc, char* argv[]) {
    // TODO: need to change:
    // 2nd: to reduce memory usage only one .xml file is being generated at one time. after maps are generated, they need to be saved to .xml before starting generation on maptrees, for example.
    CLIOptions cli = CLIOptions(argc, argv);
    if(cli.printErrors()) return 0;
    if(cli.printInfo()) return 0;

    std::vector<GBFile> gbFiles = GBFile::genGBFiles(cli);

    std::vector<Map> maps = Map::genMapFiles(gbFiles);

    MapTree mapTree = MapTree(maps);

    Database database = Database(gbFiles);    

    genProjectFolder(maps, mapTree, database);

    return 0;
}