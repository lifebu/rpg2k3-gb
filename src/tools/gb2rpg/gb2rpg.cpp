#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"


int main (int argc, char* argv[]) {
    CLIOptions cli = CLIOptions(argc, argv);

    std::vector<GBFile> f;
    f.push_back(GBFile("asdf"));
    // why does copying create a problem? Define Copy Constructor and Move Constructor?
    // https://stackoverflow.com/questions/64758775/result-type-must-be-constructible-from-value-type-of-input-range-when-trying-t
    //std::vector<GBFile> g = f;

    std::vector<GBFile> gbFiles = GBFile::genGBFiles(cli);

    std::vector<Map> maps = Map::genMapFiles(gbFiles);

    MapTree mapTree = MapTree(maps);

    Database database = Database(gbFiles);    

    genProjectFolder(maps, mapTree, database);

    return 0;
}