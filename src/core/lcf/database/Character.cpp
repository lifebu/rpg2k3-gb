#include "Character.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
Character::Character(uint16_t id, std::string name) {
    setID(id);
    setName(name);
}

uint16_t Character::getID() {
    return id;
}

void Character::setID(uint16_t val) {
    assert(1 <= val < RPGMAKER::MAX_NUM_CHARS);
    id = val;
}

std::string Character::getName() {
    return name;
}

void Character::setName(std::string val) {
    name = val;
}

};