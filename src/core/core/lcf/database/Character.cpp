#include "Character.h"

#include <cassert>

#include "core/def/RPGMaker.h"

namespace lcf {

// public
Character::Character(const uint16_t id, const std::string name) :
    id(id), name(name) {
    assert(1 <= id < RPGMAKER::MAX_NUM_CHARS);
}

};