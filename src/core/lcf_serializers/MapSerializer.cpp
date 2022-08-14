#include "MapSerializer.h"

#include "Templates.h"
#include "map/EventSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {


Map MapSerializer::FromFile(std::string fileName) {
    return Map();
}


void MapSerializer::ToFile(std::string fileName, Map& map) {
    tinyxml2::XMLDocument mapTempl(TEMPLATES::MAP);

    // Insert events into the map.
    for(auto& event : map.events) {
        auto eventDoc = EventSerializer::ToFile(event);

        eventDoc->DeepCloneInsertBack(&mapTempl, mapTempl.TraverseElement("/LMU//events"));
    }

    mapTempl.SaveFile(fileName.c_str(), false);
}

};
