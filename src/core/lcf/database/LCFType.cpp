#include "LCFType.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// LCFType
template<typename T>
LCFType<T>::LCFType(uint16_t id, std::string name, T value) :
    id(id), name(name), value(value) {
}

// Switch
Switch::Switch(const uint16_t id, const std::string name, const bool value) 
    : LCFType(id, name, value) {
    assert(1 <= value < RPGMAKER::MAX_NUM_SWITCHES);
}


// Variable
Variable::Variable(const uint16_t id, const std::string name, const int32_t value)
    : LCFType(id, name, value) {
    assert(1 <= value < RPGMAKER::MAX_NUM_VARIABLES);
}

};