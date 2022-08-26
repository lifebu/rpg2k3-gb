#include "Map.h"

#include "utilities/RPGHelper.h"

#include <iostream>

namespace lcf {

Map::Map(const int numOfEvents) {
    events.reserve(numOfEvents);
}

Event& Map::addEvent(const std::string name, const uint16_t x, const uint16_t y) {
    return events.emplace_back(getNextID(events.size()), name, x, y);
}

const uint16_t Map::nextEventID() {
    return getNextID(events.size());
}


}