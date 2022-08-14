#pragma once

#include "map/Event.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }

namespace lcf {

class Map {
    friend class MapSerializer;
public:
    Event& addEvent(std::string name, uint16_t x, uint16_t y);
    uint16_t nextEventID();

private:
    std::vector<Event> events;
};

};