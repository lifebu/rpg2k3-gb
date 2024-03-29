#pragma once

#include <cstdint>
#include <cmath>
#include <string>

#include "core/def/MemorySizes.h"

// TODO: Hacky way to get constexpr pow.
constexpr int64_t ipow(int64_t base, int exp, int64_t result = 1) {
  return exp < 1 ? result : ipow(base*base, exp/2, (exp % 2) ? result*base : result);
}

namespace RPGMAKER {
    // Ids:
    const static int INVALID_ID = 0;
    const static int MIN_ID = 1;
    const static int MAX_ID = 9999;

    // Values
    // If I use the Value Bias.
    const static bool USE_RPG_VALUE_BIAS = true;
    // Check if disabling the value_bias creates an overflow:
    static_assert(USE_RPG_VALUE_BIAS == true || MEMORYSIZES::BYTES_PER_VAR < 3, 
    "USE_RPG_VALUE_BIAS is disabled, but when using 3 Bytes per Var, the Bias is needed to avoid overflow in RPG Maker.");
    // int32_t to RPG Maker Value Bias. I want a symmetrical value range in RPG Maker. 
    // e.g. MEMORYSIZE::BYTES_PER_VAR = 3 =>
    // 2^24 = ceil((16.777.216) / 2) = 8.388.608 => RPG Maker: [-8.338.608, 8.338.607]
    const static uint32_t RPG_VALUE_BIAS = ipow(2, MEMORYSIZES::BYTES_PER_VAR*8) / 2;

    // Events:
    // How many pages one Event can have
    const static int MAX_PAGES_PER_EVENT = 100;
    // How many Lables I can have per Event Page
    const static int MAX_LABELS_PER_EPAGE = 1'000;

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

    // KeyCodes
    enum class KeyCodes
    {
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        UP = 4,
        SELECT = 5,
        CANCEL = 6,
        SHIFT = 7,
        NUMBER_0 = 10,
        NUMBER_1 = 11,
        NUMBER_2 = 12,
        NUMBER_3 = 13,
        NUMBER_4 = 14,
        NUMBER_5 = 15,
        NUMBER_6 = 16,
        NUMBER_7 = 17,
        NUMBER_8 = 18,
        NUMBER_9 = 19,
        SYMBOL_PLUS = 20,
        SYMBOL_MINUS = 21,
        SYMBOL_MUL = 22,
        SYMBOL_DIV = 23,
        SYMBOL_DOT = 24
    };
};