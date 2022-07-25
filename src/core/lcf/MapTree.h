#pragma once

#include <string>
#include <vector>

#include "MapInfo.h"

namespace lcf {

class MapTree {
    // TODO: Not that nice!
    friend class MapTreeSerializer;

public:
    /**
     * @brief Construct a new mapTree that is ready to take numMaps maps.
     * 
     * @param numMaps How many maps this mapTree will need.
     */
    MapTree(int numMaps);

    void addMapInfo(std::string mapName);
private:
    std::vector<MapInfo> mapInfos;
};

};