#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/map_tree/MapInfo.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class MapInfoSerializer : PartialSerializer<MapInfo> {
public:
    MapInfoSerializer();

    MapInfo FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(MapInfo& mapInfo) override;
};

};