#include "MapTree.h"

#include "utilities/RPGHelper.h"

namespace lcf {

// public
MapTree::MapTree(int numMaps) 
{
    mapInfos.reserve(numMaps);
}

MapInfo& MapTree::addMapInfo(std::string mapName) 
{
    return mapInfos.emplace_back(getNextID(mapInfos.size()), mapName);
}

void MapTree::addMapInfo(MapInfo& other)
{
    mapInfos.push_back(other);
}

};