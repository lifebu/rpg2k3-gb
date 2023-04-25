#pragma once

#include "map_tree/MapInfo.h"

#include <string>
#include <vector>

namespace lcf 
{

class MapTree 
{
    friend class MapTreeSerializer;

public:
    /**
     * @brief Construct a new mapTree that is ready to take numMaps maps.
     * 
     * @param numMaps How many maps this mapTree will need.
     */
    MapTree(int numMaps = 0);

    MapInfo& addMapInfo(std::string mapName);
    void addMapInfo(MapInfo& other);

private:
    std::vector<MapInfo> mapInfos;
};

};