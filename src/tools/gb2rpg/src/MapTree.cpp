#include "MapTree.h"

#include "GBFile.h"
#include "Globals.h"

#include "core/def/Globals.h"
#include "core/lcf_serializers/MapTreeSerializer.h"

#include <iostream>

using namespace gb2rpg;

void MapTree::genMapTree(std::vector<GBFile>& gbFiles) 
{
    lcf::MapTree mapTree(gbFiles.size());

    std::cout << "Generating Maptree: RPG_RT.emt\n";

    for(auto& gbFile : gbFiles) 
    {
        std::string mapName = gbFile.getTitle();
        mapTree.addMapInfo(mapName);
    }

    std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::MAPTREE_FILE;
    lcf::MapTreeSerializer::ToFile(filePath, mapTree);
}