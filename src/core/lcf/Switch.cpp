#include "Switch.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
Switch::Switch(uint16_t id, std::string name, bool value) {
    setID(id);
    setName(name);
    setValue(value);
}

uint16_t Switch::getID() {
    return id;
}

void Switch::setID(uint16_t val) {
    assert(1 <= val < RPGMAKER::MAX_NUM_SWITCHES);
    id = val;
}

std::string Switch::getName() {
    return name;
}

void Switch::setName(std::string val) {
    name = val;
}

bool Switch::getValue() {
    return value;
}

void Switch::setValue(bool val) {
    value = val;
}

};