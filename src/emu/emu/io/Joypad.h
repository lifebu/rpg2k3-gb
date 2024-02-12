#pragma once

#include <utility>

namespace emu
{

// Responsible for updating the Joypad.
// It reads the state of the RPG Maker and updates the Joypad Bytes accordingly.
class Joypad
{
public:
    // Shifting offsets:
    constexpr static uint8_t JOYPAD_SELECT_BUTTONS  = 5;
    constexpr static uint8_t JOYPAD_SELECT_DPAD     = 4;
    constexpr static uint8_t JOYPAD_START_OR_DOWN   = 3;
    constexpr static uint8_t JOYPAD_SELECT_OR_UP    = 2;
    constexpr static uint8_t JOYPAD_B_OR_LEFT       = 1;
    constexpr static uint8_t JOYPAD_A_OR_RIGHT      = 0;

    static void Init();
    static void Update();
};

};