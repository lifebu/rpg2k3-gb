#include "LCFType.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// LCFType
template<typename T>
LCFType<T>::LCFType(uint16_t id, std::string name, T value) :
    id(id), name(name), value(value) {
}

template<typename T>
T LCFType<T>::getValue() {
    return value;
}

template<typename T>
void LCFType<T>::setValue(T val) {
    value = val;
}

// Switch
Switch::Switch(uint16_t id, std::string name, bool value) 
    : LCFType(id, name, value) {
    assert(1 <= value < RPGMAKER::MAX_NUM_SWITCHES);
}


// Variable
Variable::Variable(uint16_t id, std::string name, int32_t value)
    : LCFType(id, name, value) {
    assert(1 <= value < RPGMAKER::MAX_NUM_VARIABLES);
}

};