#include "MapInfoSerializer.h"

#include "lcf_serializers/Templates.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

MapInfo MapInfoSerializer::FromFile(std::string fileName) {
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return MapInfo(id, name);
    }

    auto* nameElem = file.TraverseElement("/MapInfo/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");

    return MapInfo(id, name);
}

std::unique_ptr<tinyxml2::XMLDocument> MapInfoSerializer::ToFile(MapInfo& mapInfo) {
    auto mapInfoTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::MAP_INFO);

    // Set Map ID
    mapInfoTempl->RootElement()->SetAttribute("id", generateID(mapInfo.getID()).c_str());

    // Change map name to filename.
    auto* name = mapInfoTempl->TraverseElement("/MapInfo/name")->FirstChild()->ToText();
    name->SetValue(mapInfo.getName().c_str());

    return mapInfoTempl;
}

};
