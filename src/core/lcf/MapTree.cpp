#include "MapTree.h"

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
MapTree::MapTree(int numMaps) {
    mapInfos.reserve(numMaps);
}

void MapTree::addMapInfo(std::string mapName) {
    mapInfos.emplace_back(getNextID(mapInfos.size()), mapName);
}

};