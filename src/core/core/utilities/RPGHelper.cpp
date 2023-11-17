#include "RPGHelper.h"

#include "core/pch.h"

template<uint8_t N, bool USE_BIAS, uint32_t BIAS>
inline int32_t packBytes(std::array<uint8_t, N> bytes)
{
    int32_t var = 0;

    for(int i = 0; i < N; ++i) 
    {
        var += bytes.at(i) << (i * 8);
    }

    if (USE_BIAS) 
        var -= BIAS;
    
    return var;
}

template<uint8_t N, bool USE_BIAS, uint32_t BIAS>
inline std::array<uint8_t, N> unpackBytes(int32_t var)
{
    if (USE_BIAS)
        var += BIAS;

    std::array<uint8_t, N> bytes;
    for(int i = 0; i < N; ++i) 
    {
        // all 8 Bits are 1.
        uint32_t mask = 255;
        uint32_t byte = var & mask;
        var = var >> 8;
        bytes[i] = byte;
    }

    return bytes;
}

int32_t packVariable(std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes)
{
    return packBytes<MEMORYSIZES::BYTES_PER_VAR, RPGMAKER::USE_RPG_VALUE_BIAS, RPGMAKER::RPG_VALUE_BIAS>(bytes);
}

std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> unpackVariable(int32_t var) 
{
    return unpackBytes<MEMORYSIZES::BYTES_PER_VAR, RPGMAKER::USE_RPG_VALUE_BIAS, RPGMAKER::RPG_VALUE_BIAS>(var);
}

uint16_t packMapPosition(std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes)
{
    return packBytes<MEMORYSIZES::BYTES_PER_EVENT_POS, false, 0>(bytes);
}

std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> unpackMapPosition(uint16_t var)
{
    return unpackBytes<MEMORYSIZES::BYTES_PER_EVENT_POS, false, 0>(var);
}

uint16_t packEXP(std::array<uint8_t, MEMORYSIZES::BYTES_PER_EXP> bytes)
{
    return packBytes<MEMORYSIZES::BYTES_PER_EXP, false, 0>(bytes);
}

std::array<uint8_t, MEMORYSIZES::BYTES_PER_EXP> unpackEXP(uint16_t var)
{
    return unpackBytes<MEMORYSIZES::BYTES_PER_EXP, false, 0>(var);
}

std::string generateID(int id) 
{
    assert(id > 0 && id < 10000);
    std::string str;
    // Add leading zeroes.
    if (id < 1000) str += "0";
    if (id < 100) str += "0";
    if (id < 10) str += "0";

    str += std::to_string(id);

    return str;
}