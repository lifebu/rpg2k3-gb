#include "src/GBFile.h"
#include "src/CLI.h"
#include "src/Map.h"
#include "src/MapTree.h"
#include "src/Database.h"
#include "src/ProjectGenerator.h"

#include "core/structure/Logger.h"

int main (int argc, char* argv[]) 
{
    core::Logger logger;
    logger.Init("gb2rpg_", core::LOGMASK::LOG_MODE_FILE | core::LOGMASK::LOG_MODE_STDOUT);

    gb2rpg::CLIOptions cli = gb2rpg::CLIOptions(argc, argv);
    if(cli.shouldEnd()) return 0;
    
    gb2rpg::ProjectGenerator::cleanProjectFolder(); 

    if(cli.stopAfterClean()) return 0;

    gb2rpg::GBFileGenerator gbGen;
    std::vector<gb2rpg::GBFile> gbFiles = gbGen.genGBFiles(cli);
    if(gbGen.hadErrors()) return 0;
    
    gb2rpg::Map::genMapFiles(gbFiles, cli.getXMLParser());
    
    gb2rpg::MapTree::genMapTree(gbFiles);
    
    gb2rpg::Database::genDatabase();

    gb2rpg::ProjectGenerator::genProjectFolder(gbFiles.size());
    
    return 0;
}