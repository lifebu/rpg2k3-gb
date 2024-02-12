#include "MBC.h"

#include <core/utilities/GBHelper.h>

#include "emu/memory/MMU.h"
#include "emu/def/EmuState.h"

namespace emu
{

void MBC::Init()
{
    // TODO: Would be nice to have a structure somewhere for the Cartridge Header Offsets. Or just save the values somewhere to access them (static memory).
    uint8_t cartridgeType = MMU::ReadByte(0x147);

    if (cartridgeType == 0x00)
    {
        m_Type = MBC_TYPE::NO_MBC;
    }
    else if(cartridgeType >= 0x01 && cartridgeType <= 0x03)
    {
        m_Type = MBC_TYPE::MBC1;
        uint8_t romSize = MMU::ReadByte(0x148);
        const int romSizeKByte = ConvertROMSizetoKByte(romSize);
        m_NumROMBanks = romSizeKByte / ROM_BANK_SIZE_KBYTE;

        m_UseSecondRegisterForROM = romSizeKByte >= 1'024;

        uint8_t ramSize = MMU::ReadByte(0x149);
        const int ramSizeKByte = ConvertRAMSizetoKByte(ramSize);
        m_NumRAMBanks = ramSizeKByte / RAM_BANK_SIZE_KBYTE;

        auto* const emuState = EmuState::Get();
        assert(emuState);

        emuState->lowRomBankIndex = 0;
        emuState->highRomBankIndex = 1;
        emuState->ramBankIndex = 0;
    }
    else if (cartridgeType >= 0x05 && cartridgeType <= 0x06)
    {
        m_Type = MBC_TYPE::MBC2;
    }
    else if (cartridgeType >= 0x0F && cartridgeType <= 0x13)
    {
        m_Type = MBC_TYPE::MBC3;
    }
    else if (cartridgeType == 0x19 || 
            (cartridgeType >= 0x1A && cartridgeType <= 0x1E))
    {
        m_Type = MBC_TYPE::MBC5;
    }
    else if (cartridgeType == 0x20)
    {
        m_Type = MBC_TYPE::MBC6;
    }
    else if (cartridgeType == 0x22)
    {
        m_Type = MBC_TYPE::MBC7;
    }
    else if (cartridgeType >= 0x0B && cartridgeType <= 0x0D)
    {
        m_Type = MBC_TYPE::MMM01;
    }
    else if (cartridgeType == 0xFF)
    {
        m_Type = MBC_TYPE::HUC1;
    }
    else if (cartridgeType == 0xFE)
    {
        m_Type = MBC_TYPE::HUC3;
    }
    else
    {
        assert(false && "Unknown MBC cartridge type encountered!");
    }
}

void MBC::WriteByte(uint16_t address, uint8_t value)
{
    assert(m_Type == MBC_TYPE::NO_MBC); // TODO: Just for testing only allow cartridges with NO_MBC.

#if 1 // TODO: For now we don't support MBCs => do that later!
return;
#else

    if(address >= RAM_ENABLE.first && address <= RAM_ENABLE.second)
    {
        m_RAMEnable = value == RAM_ENABLE_VALUE;
    } 
    else if(address >= ROM_BANK.first && address <= ROM_BANK.second)
    {
        uint8_t romBankValue = value & ROM_REGISTER_MASK;

        if(romBankValue == 0) // Zero Translation
            romBankValue = 1;

        // Filter for only the bits we need.
        romBankValue = romBankValue & (m_NumROMBanks - 1);

        m_ROMBank = romBankValue;
    }
    else if(address >= RAM_BANK.first && address <= RAM_BANK.second)
    {
        const uint8_t ramBankValue = value & RAM_REGISTER_MASK;
        m_RAMBank = ramBankValue;
    }
    else if(address >= BANKING_MODE.first && address <= BANKING_MODE.second)
    {
        uint8_t bankingModeValue = value & BANKING_MODE_MASK;
        m_BankingMode = static_cast<MBC_BANKING_MODE>(bankingModeValue);
    }

    auto* const emuState = EmuState::Get();
    assert(emuState);

    if(m_UseSecondRegisterForROM)
    {
        emuState->highRomBankIndex = m_ROMBank + (m_RAMBank << 5);
    }
    else
    {
        emuState->highRomBankIndex = m_ROMBank;
    }

    if(m_BankingMode == MBC_BANKING_MODE::MODE_1)
    {
        
    }
#endif 
}

};