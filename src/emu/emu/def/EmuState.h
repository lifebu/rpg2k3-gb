#pragma once

#include <cstdint>

#include <core/structure/Singleton.h>

// TODO: This might be could candidates to be static variables later :)
// TODO: This as a singleton is also not very good to have shared state like this, but fine for now.
class EmuState : public Singleton<EmuState>
{
public:
    //////////////////////////////////////////////////////////// 
    // Cartridge
    // Which Rom bank is currently laoded for the low 16kByte Region (up to 512 Banks). Defauls to 1st.
    uint16_t lowRomBankIndex = 0;
    // Which Rom bank is currently loaded for the high 16kByte Region (up to 512 Banks). Defaults to 2nd bank.
    uint16_t highRomBankIndex = 1;
    // Which Ram bank is currently loaded (up to 8).
    uint8_t ramBankIndex = 0;

    /////////////////////////////////////////////////////////// 
    // OAM

    /////////////////////////////////////////////////////////// 
    // Input

    /////////////////////////////////////////////////////////// 
    // Serial

    /////////////////////////////////////////////////////////// 
    // Timer

    /////////////////////////////////////////////////////////// 
    // Audio

    /////////////////////////////////////////////////////////// 
    // LCD

    /////////////////////////////////////////////////////////// 
    // Boot Rom
    bool bootRomEnabled = false;
    
    /////////////////////////////////////////////////////////// 
    // Interrupts

    /////////////////////////////////////////////////////////// 
    // CPU Registers
    // The stop instruction can enable this.
    // TODO: This also needs to reset the Timer Divider.
    bool isStopped = false;

    /////////////////////////////////////////////////////////// 
    // Emulator
    bool isInitialized = false;
};
