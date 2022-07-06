#pragma once

// TODO would be nice to have this in a .cpp file, but then core needs to be compiled as a library like tinyxml.
// TODO If this is not a .h and .cpp and I include the .h multiple times I get compiler errors (Like Map.h and MapTree.h).
#include<vector>
#include<cstdint>
#include<string>
#include<cassert>

#include "src/core/VarMapping.h"
#include "src/core/MemorySizes.h"
#include "src/core/RPGMaker.h"


int32_t packVariable(std::vector<uint8_t> bytes) {
    assert(bytes.size() == MEMORYSIZES::BYTES_PER_VAR);
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
    for(int i = 0; i < MEMORYSIZES::BYTES_PER_VAR; ++i) {
        // all 8 Bits are 1.
        uint32_t mask = 255;
        uint32_t byte = var & mask;
        var = var >> 8;
        bytes.push_back(byte);
    }
    assert(bytes.size() == MEMORYSIZES::BYTES_PER_VAR);
    return bytes;
};

std::string generateID(int id) {
    assert(id > 0 && id < 10000);
    std::string str;
    // Add leading zeroes.
    if (id < 1000) str += "0";
    if (id < 100) str += "0";
    if (id < 10) str += "0";

    str += std::to_string(id);

    return str;
}