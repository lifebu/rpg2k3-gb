#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"

int main (int argc, char* argv[]) {
    ProjectGenerator::cleanProjectFolder();    

    CLIOptions cli = CLIOptions(argc, argv);
    if(cli.shouldEnd()) return 0;
    
    GBFileGenerator gbGen;
    std::vector<GBFile> gbFiles = gbGen.genGBFiles(cli);
    if(gbGen.hadErrors()) return 0;
    
    Map::genMapFiles(gbFiles);
    
    MapTree::genMapTree(gbFiles);
    
    Database::genDatabase();

    ProjectGenerator::genProjectFolder(gbFiles.size());

    return 0;
}