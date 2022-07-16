#include "Variable.h"


namespace lcf {

// public
Variable::Variable(std::string name, uint16_t id, int32_t value = 0) :
    name(name), id(id), value(value) {

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
    id = val;
}

int32_t Variable::getValue() {
    return value;
}

void Variable::setValue(int32_t val) {
    value = val;
}

};