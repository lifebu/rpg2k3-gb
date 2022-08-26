#include "MapInfoSerializer.h"

#include "lcf_serializers/Templates.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

MapInfoSerializer::MapInfoSerializer() {}

MapInfo MapInfoSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) {
    return MapInfo(0, "");
}

std::unique_ptr<tinyxml2::XMLDocument> MapInfoSerializer::ToFile(MapInfo& mapInfo) {
    auto mapInfoTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::MAP_INFO);

    // Set Map ID
    mapInfoTempl->RootElement()->SetAttribute("id", generateID(mapInfo.id).c_str());

    // Change map name to filename.
    auto* name = mapInfoTempl->TraverseElement("/MapInfo/name")->FirstChild()->ToText();
    name->SetValue(mapInfo.name.c_str());

    return mapInfoTempl;
}

};
