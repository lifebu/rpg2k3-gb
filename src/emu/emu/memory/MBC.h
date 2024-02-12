#pragma once

#include <cstdint>

#include <core/structure/Singleton.h>

namespace emu
{

// Memory Bank Controller
class MBC : public Singleton<MBC>
{
public:
    // Initializes the actual type of the MBC.
    void Init();

    void WriteByte(uint16_t address, uint8_t value);
private:
    // TODO: IMPLEMENT LATER!
    // TODO: Maybe just create a factory function or something here that returns the correct MBC type? Than the code for the different MBC is seperated. But it might be that they are super similar. Then a set of functions that another class can use for the common behaviour could be better. Let's see!
    enum class MBC_TYPE: uint8_t
    {
        INVALID = 0,
        // 0x00, 
        NO_MBC,
        // 0x01, 0x02, 0x03
        MBC1,
        // 0x05, 0x06
        MBC2, 
        // 0x0F, 0x10, 0x11, 0x12, 0x13
        MBC3, 
        // 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E
        MBC5,
        // 0x20
        MBC6,
        // 0x22
        MBC7,
        // 0x0B, 0x0C, 0x0D
        MMM01,
        // 0xFF
        HUC1,
        // 0xFE
        HUC3,
    };
    MBC_TYPE m_Type = MBC_TYPE::INVALID;

    // TODO: This should be a constants somewhere else wher it can be reused.
    constexpr static int ROM_BANK_SIZE_KBYTE = 16;
    constexpr static int RAM_BANK_SIZE_KBYTE = 8;

    // MBC1:
    // Memory Ranges:
    constexpr static std::pair<uint16_t, uint16_t> RAM_ENABLE = 
                                    std::make_pair(0x0000, 0x1FFF);
    constexpr static std::pair<uint16_t, uint16_t> ROM_BANK = 
                                    std::make_pair(0x2000, 0x3FFF);
    constexpr static std::pair<uint16_t, uint16_t> RAM_BANK = 
                                    std::make_pair(0x4000, 0x5FFF);
    constexpr static std::pair<uint16_t, uint16_t> BANKING_MODE = 
                                    std::make_pair(0x6000, 0x7FFF);

    // Constants:
    const uint8_t RAM_ENABLE_VALUE = 0xA;
    const uint8_t ROM_REGISTER_MASK = 0b11111;
    const uint8_t RAM_REGISTER_MASK = 0b11;
    const uint8_t BANKING_MODE_MASK = 0b1;

    // State:
    bool m_UseSecondRegisterForROM = false;
    
    enum class MBC_BANKING_MODE: int8_t
    {
        INVALID = -1,
        MODE_0,
        MODE_1
    };
    MBC_BANKING_MODE m_BankingMode = MBC_BANKING_MODE::MODE_0;
    
    bool m_RAMEnable = false;
    uint8_t m_ROMBank = 0;
    uint8_t m_RAMBank = 0;
    uint8_t m_NumROMBanks = 0;
    uint8_t m_NumRAMBanks = 0;

    /*
    MBC 1:
        - ROMSize.
    */

};

};