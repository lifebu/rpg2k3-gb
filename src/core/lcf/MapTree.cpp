#include "MapTree.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
MapTree::MapTree(int numMaps) {
    mapInfos.reserve(numMaps);
}

void MapTree::addMapInfo(std::string mapName) {
    uint16_t nextID = 1 + mapInfos.size();
    mapInfos.emplace_back(MapInfo(nextID, mapName));
}

};