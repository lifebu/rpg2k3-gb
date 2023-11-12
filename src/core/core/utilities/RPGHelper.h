#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <utility>
#include <string>

#include "core/def/VarMapping.h"
#include "core/def/MemorySizes.h"
#include "core/def/RPGMaker.h"

int32_t packVariable(std::vector<uint8_t> bytes);
std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> unpackVariable(int32_t var);

uint16_t packMapPosition(std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes);
std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> unpackMapPosition(uint16_t var);

std::string generateID(int id);

// Generate the next ID given the number of elements that already exist.
constexpr uint16_t getNextID(int numElems) {
    return static_cast<uint16_t>(RPGMAKER::MIN_ID + numElems);
}

constexpr uint16_t getIndexFromID(int id) {
    return id - RPGMAKER::MIN_ID;
}