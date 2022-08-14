#include "Item.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
Item::Item(uint16_t id, std::string name, ItemType type) {
    setID(id);
    setName(name);
    setType(type);
}

uint16_t Item::getID() {
    return id;
}

void Item::setID(uint16_t val) {
    assert(1 <= val < RPGMAKER::MAX_NUM_ITEMS);
    id = val;
}

std::string Item::getName() {
    return name;
}

void Item::setName(std::string val) {
    name = val;
}

ItemType Item::getType() {
    return type;
}

void Item::setType(ItemType val) {
    type = val;
}

};