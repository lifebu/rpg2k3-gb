#include "MMIO.h"

#include <core/emu_interface/RPGMakerInterface.h>

#include "emu/pch.h"
#include "emu/memory/MMU.h"

namespace emu
{
void MMIO::Init()
{
    // Setup Input Memory (all to 1).
    MMU::WriteByte(MMU::JOYPAD.first, 0xFF);
}

void MMIO::Update()
{
    // Joypad
    uint8_t joypad = MMU::ReadByte(MMU::JOYPAD.first);

    // GB sees a "0" as button pressed, so everything needs to be inverted.
    const bool selectButtons = !(joypad & (1 << JOYPAD_SELECT_BUTTONS));
    const bool selectDpad = !(joypad & (1 << JOYPAD_SELECT_DPAD));
    
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // Default if neither or both are set => no input is pressed.
    uint8_t lowNibble = 0x0F; 

    if(selectDpad && !selectButtons)
    {
        lowNibble = 
            // GB: Down
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::DOWN)  << JOYPAD_START_OR_DOWN) | 
            // GB: Up
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::UP)    << JOYPAD_SELECT_OR_UP) | 
            // GB: Left
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::LEFT)  << JOYPAD_B_OR_LEFT) | 
            // GB: Right
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::RIGHT) << JOYPAD_A_OR_RIGHT);  
    }
    else if (!selectDpad && selectButtons)
    {
        lowNibble = 
            // GB: Start
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::NUMBER_1) << JOYPAD_START_OR_DOWN) | 
            // GB: Select
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::NUMBER_2) << JOYPAD_SELECT_OR_UP) | 
            // GB: B
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::NUMBER_3) << JOYPAD_B_OR_LEFT) | 
            // GB: A
            (!rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::NUMBER_4) << JOYPAD_A_OR_RIGHT);
    }

    // 0xF0 is high-nibble mask.
    joypad = joypad & (lowNibble | 0xF0);

    MMU::WriteByte(MMU::JOYPAD.first, joypad);
}

};