#pragma once

#include "MemorySizes.h"

#include <cstdint>
#include <cmath>
#include <string>

namespace RPGMAKER {
    // Ids:
    const static int MIN_ID = 1;
    const static int MAX_ID = 9999;

    // Values
    // If I use the Value Bias.
    const static bool USE_RPG_VALUE_BIAS = true;
    // Check if disabling the value_bias creates an overflow:
    static_assert(USE_RPG_VALUE_BIAS == false && MEMORYSIZES::BYTES_PER_VAR < 3 || USE_RPG_VALUE_BIAS == true, 
    "USE_RPG_VALUE_BIAS is disabled, but when using 3 Bytes per Var, the Bias is needed to avoid overflow in RPG Maker.");
    // int32_t to RPG Maker Value Bias. I want a symmetrical value range in RPG Maker. 
    // e.g. MEMORYSIZE::BYTES_PER_VAR = 3 =>
    // 2^24 = ceil((16.777.216) / 2) = 8.388.608 => RPG Maker: [-8.338.608, 8.338.607]
    const static uint32_t RPG_VALUE_BIAS = std::pow(2, MEMORYSIZES::BYTES_PER_VAR*8) / 2;

    // Map
    const static int MAP_SIZE_X = 500;
    const static int MAP_SIZE_Y = 500;

    // Database
    // TODO: Version 1.08 only supports 5k switches/variable, the steam version 1.12a supports up to 10k switches/variables
    const static int MAX_NUM_SWITCHES = 10000;
    const static int MAX_NUM_VARIABLES = 10000;
    const static int MAX_NUM_ITEMS = 10000;
    // Testing showed, that the RPG Maker will crash with more than 2910 characters.
    const static int MAX_NUM_CHARS = 2910;

    // Items
    const static int WEAPON_ID = 1;
    const static int SHIELD_ID = 2;
    const static int BODY_ID = 3;
    const static int HEAD_ID = 4;
    const static int ACCESSORY_ID = 5;
    const std::string ITEM_NAMES[6] = { "0", "WPN", "SHLD", "BODY", "HEAD", "ACCES"};
};