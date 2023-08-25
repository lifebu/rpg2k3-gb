#include "MapTree.h"

#include <core/def/Globals.h>
#include <core/lcf_serializers/MapTreeSerializer.h>
#include <core/structure/Logger.h>

#include "gb2rpg/def/Globals.h"
#include "gb2rpg/file/GBFile.h"


using namespace gb2rpg;

void MapTree::genMapTree(std::vector<GBFile>& gbFiles) 
{
    lcf::MapTree mapTree(gbFiles.size());

    core::Logger::Get()->Log("Generating Maptree: RPG_RT.emt", core::LogLevel::INFO);

    for(auto& gbFile : gbFiles) 
    {
        std::string mapName = gbFile.getTitle();
        mapTree.addMapInfo(mapName);
    }

    std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::MAPTREE_FILE;
    lcf::MapTreeSerializer::ToFile(filePath, mapTree);
}