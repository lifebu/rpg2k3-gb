#include "MapInfo.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
MapInfo::MapInfo(uint16_t id, std::string name) {
    setName(name);
    setID(id);
}

uint16_t MapInfo::getID() {
    return id;
}

void MapInfo::setID(uint16_t val) {
    assert(1 <= val < RPGMAKER::MAX_ID);
    id = val;
}

std::string MapInfo::getName() {
    return name;
}

void MapInfo::setName(std::string val) {
    name = val;
}

};