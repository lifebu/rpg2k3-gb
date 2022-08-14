#pragma once

#include "lcf/map_tree/MapInfo.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class MapInfoSerializer {
public:
    MapInfoSerializer() = delete;

    static MapInfo FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(MapInfo& mapInfo);
};

};