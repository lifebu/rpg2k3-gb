#include "Variable.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
Variable::Variable(uint16_t id, std::string name, int32_t value) {
    setID(id);
    setName(name);
    setValue(value);
}

std::string Variable::getName() {
    return name;
}

void Variable::setName(std::string val) {
    name = val;
}

uint16_t Variable::getID() {
    return id;
}

void Variable::setID(uint16_t val) {
    assert(1 <= val < RPGMAKER::MAX_NUM_VARIABLES);
    id = val;
}

int32_t Variable::getValue() {
    return value;
}

void Variable::setValue(int32_t val) {
    value = val;
}

};