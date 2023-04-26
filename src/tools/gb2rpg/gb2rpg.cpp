#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"

int main (int argc, char* argv[]) 
{
    gb2rpg::ProjectGenerator::cleanProjectFolder();    

    gb2rpg::CLIOptions cli = gb2rpg::CLIOptions(argc, argv);
    if(cli.shouldEnd()) return 0;
    
    gb2rpg::GBFileGenerator gbGen;
    std::vector<gb2rpg::GBFile> gbFiles = gbGen.genGBFiles(cli);
    if(gbGen.hadErrors()) return 0;
    
    gb2rpg::Map::genMapFiles(gbFiles);
    
    gb2rpg::MapTree::genMapTree(gbFiles);
    
    gb2rpg::Database::genDatabase();

    gb2rpg::ProjectGenerator::genProjectFolder(gbFiles.size());

    return 0;
}