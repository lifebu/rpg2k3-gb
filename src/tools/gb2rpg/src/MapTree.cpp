#include "MapTree.h"

#include "GBFile.h"
#include "Globals.h"

#include "src/core/lcf/MapTree.h"
#include "src/core/lcf_serializers/MapTreeSerializer.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

using namespace gb2rpg;

void MapTree::genMapTree(std::vector<GBFile>& gbFiles) {
    lcf::MapTree mapTree(gbFiles.size());

    for(auto& gbFile : gbFiles) {
        std::string mapName = gbFile.getTitle();
        mapTree.addMapInfo(mapName);
    }

    std::string filePath = PROJECT::PROJECT_DIR + EXPORTS::MAPTREE_FILE;
    lcf::MapTreeSerializer::ToFile(filePath, mapTree);
}