#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "../def/VarMapping.h"
#include "../def/MemorySizes.h"
#include "../def/RPGMaker.h"


int32_t packVariable(std::vector<uint8_t> bytes);
std::vector<uint8_t> unpackVariable(int32_t var);
std::string generateID(int id);
// Generate the next ID given the number of elements that already exist.

constexpr uint16_t getNextID(int numElems) {
    return RPGMAKER::MIN_ID + numElems;
}