#include "Item.h"

#include "core/pch.h"

#include "core/def/RPGMaker.h"


namespace lcf {

// public
Item::Item(const uint16_t id, const std::string name, const ItemType type) :
        id(id), name(name), type(type) {
    assert(1 <= id < RPGMAKER::MAX_NUM_ITEMS);
}

uint16_t Item::GetID() const
{
    return id;
}
};