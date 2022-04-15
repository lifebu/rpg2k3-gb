#include "RPGHelper.h"

#include "Globals.h"

#include <cassert>

int32_t packVariable(std::vector<uint8_t> bytes) {
    assert(bytes.size() == MEMORYSIZE::BYTES_PER_VAR);
    int32_t var = 0;
    for(int i = 0; i < bytes.size(); ++i) {
        var += bytes.at(i) << (i * 8);
    }
    if (RPGMAKER::USE_RPG_VALUE_BIAS) 
        var -= RPGMAKER::RPG_VALUE_BIAS;
    
    return var;
};

std::vector<uint8_t> unpackVariable(int32_t var) {
    if (RPGMAKER::USE_RPG_VALUE_BIAS)
        var += RPGMAKER::RPG_VALUE_BIAS;
    
    std::vector<uint8_t> bytes;
    for(int i = 0; i < MEMORYSIZE::BYTES_PER_VAR; ++i) {
        // all 8 Bits are 1.
        uint32_t mask = 255;
        uint32_t byte = var & mask;
        var = var >> 8;
        bytes.push_back(byte);
    }
    assert(bytes.size() == MEMORYSIZE::BYTES_PER_VAR);
    return bytes;
};