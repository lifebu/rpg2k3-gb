#include "Map.h"

#include "src/core/utilities/RPGHelper.h"

#include <iostream>

namespace lcf {

Event& Map::addEvent(std::string name, uint16_t x, uint16_t y) {
    return events.emplace_back(getNextID(events.size()), name, x, y);
}

uint16_t Map::nextEventID() {
    return getNextID(events.size());
}


}