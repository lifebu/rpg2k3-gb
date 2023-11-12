#include "RPGHelper.h"

#include "core/pch.h"


int32_t packVariable(std::vector<uint8_t> bytes) {
    assert(bytes.size() == MEMORYSIZES::BYTES_PER_VAR);
    int32_t var = 0;
    for(int i = 0; i < MEMORYSIZES::BYTES_PER_VAR; ++i) {
        var += bytes.at(i) << (i * 8);
    }
    if (RPGMAKER::USE_RPG_VALUE_BIAS) 
        var -= RPGMAKER::RPG_VALUE_BIAS;
    
    return var;
}

std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> unpackVariable(int32_t var) {
    if (RPGMAKER::USE_RPG_VALUE_BIAS)
        var += RPGMAKER::RPG_VALUE_BIAS;

    std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes;
    for(int i = 0; i < MEMORYSIZES::BYTES_PER_VAR; ++i) {
        // all 8 Bits are 1.
        uint32_t mask = 255;
        uint32_t byte = var & mask;
        var = var >> 8;
        bytes[i] = byte;
    }

    return bytes;
}

uint16_t packMapPosition(std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes)
{
    // TODO: This is the same code as pack variable, just without the bias added.
    // TODO: And a helper version that also packs the position into one would be neat!
    assert(bytes.size() == MEMORYSIZES::BYTES_PER_EVENT_POS);
    int32_t var = 0;
    for(int i = 0; i < MEMORYSIZES::BYTES_PER_EVENT_POS; ++i) 
    {
        var += bytes.at(i) << (i * 8);
    }

    return var;
}

std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> unpackMapPosition(uint16_t var)
{
    // TODO: This is the same code as pack variable, just without the bias added.
    // TODO: And a helper version that also unpacks the position into one would be neat!
    std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes;
    for(int i = 0; i < MEMORYSIZES::BYTES_PER_EVENT_POS; ++i) 
    {
        // all 8 Bits are 1.
        uint32_t mask = 255;
        uint32_t byte = var & mask;
        var = var >> 8;
        bytes[i] = byte;
    }

    return bytes;
}

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