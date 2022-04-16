#pragma once

#include "MemorySizes.h"

#include <cstdint>

namespace RPGMAKER {
    // If I use the Value Bias.
    const static bool USE_RPG_VALUE_BIAS = false;
    // Check if disabling the value_bias creates an overflow:
    static_assert(USE_RPG_VALUE_BIAS == false && MEMORYSIZES::BYTES_PER_VAR < 3 || USE_RPG_VALUE_BIAS == true, 
    "USE_RPG_VALUE_BIAS is disabled, but when using 3 Bytes per Var, the Bias is needed to avoid overflow in RPG Maker.");
    // int32_t to RPG Maker Value Bias. I want a symmetrical value range in RPG Maker. 
    // e.g. MEMORYSIZE::BYTES_PER_VAR = 3 =>
    // 2^24 = ceil((16.777.216) / 2) = 8.388.608 => RPG Maker: [-8.338.608, 8.338.607]
    const static uint32_t RPG_VALUE_BIAS = pow(2, MEMORYSIZES::BYTES_PER_VAR*8) / 2;

    // Map
    const static int MAP_SIZE_X = 500;
    const static int MAP_SIZE_Y = 500;
};