#include "Item.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
Item::Item(const uint16_t id, const std::string name, const ItemType type) :
        id(id), name(name), type(type) {
    assert(1 <= id < RPGMAKER::MAX_NUM_ITEMS);
}

};