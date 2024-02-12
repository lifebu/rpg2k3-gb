#include "MMU.h"

#include "emu/pch.h"

#include <core/def/MemorySizes.h>
#include <core/def/VarMapping.h>
#include <core/emu_interface/RPGMakerInterface.h>
#include <core/utilities/RPGHelper.h>

#include "emu/def/EmuState.h"
#include "emu/memory/MBC.h"

namespace emu
{

uint8_t MMU::ReadByte(uint16_t address)
{
    if(IsMapROMAddress(address))
    {
        uint32_t mapROMAddress = GBAddressToMapROM(address);
        uint32_t mapROMValue = ReadMapROM(mapROMAddress);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes = unpackVariable(mapROMValue);
        return bytes.at(address % MEMORYSIZES::BYTES_PER_VAR);
    }
    else if(IsMapRAMAddress(address))
    {
        uint32_t mapRamAddress = GBAddressToMapRAM(address);
        uint32_t packedValue = ReadMapRAM(mapRamAddress);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes = unpackMapPosition(packedValue);
        return bytes.at(mapRamAddress % MEMORYSIZES::BYTES_PER_EVENT_POS);
    }
    else if (IsCharaRAMAddress(address))
    {
        uint32_t charaRAMAddress = GBAddressToCharaRAM(address);
        int32_t packedValue = ReadCharaRAM(charaRAMAddress);
        if(IsCharaRAMAddressPacked(charaRAMAddress))
        {
            std::array<uint8_t, MEMORYSIZES::BYTES_PER_EXP> bytes = unpackEXP(packedValue);
            const uint8_t offset = charaRAMAddress % MEMORYSIZES::BYTES_PER_CHAR;
            return bytes.at(offset);
        }
        else
        {
            return packedValue;
        }
    }
    else if (IsKnownUnsupportedRAM(address))
    {
    }
    else
    {
        assert(false && "Unsupported memory read detected!");
    }

    return 0xFF;
}

void MMU::WriteByte(uint16_t address, uint8_t value)
{
    if(IsMapROMAddress(address))
    {
        auto* const mbc = MBC::Get();
        assert(mbc);

        mbc->WriteByte(address, value);
    }
    else if(IsMapRAMAddress(address))
    {
        uint16_t mapRAMAddress = GBAddressToMapRAM(address);
        uint32_t packedValue = ReadMapRAM(mapRAMAddress);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes = unpackMapPosition(packedValue);
        bytes.at(mapRAMAddress % MEMORYSIZES::BYTES_PER_EVENT_POS) = value;
        packedValue = packMapPosition(bytes);

        WriteMapRAM(mapRAMAddress, packedValue);
    }
    else if (IsCharaRAMAddress(address))
    {
        uint32_t charaRAMAddress = GBAddressToCharaRAM(address);
        if(IsCharaRAMAddressPacked(charaRAMAddress))
        {
            int32_t packedValue = ReadCharaRAM(charaRAMAddress);
            std::array<uint8_t, MEMORYSIZES::BYTES_PER_EXP> bytes = unpackEXP(packedValue);
            const uint8_t offset = charaRAMAddress % MEMORYSIZES::BYTES_PER_CHAR;
            bytes.at(offset) = value;
            packedValue = packEXP(bytes);
            WriteCharaRAM(charaRAMAddress, packedValue);
        }
        else
        {
            WriteCharaRAM(charaRAMAddress, value);
        }
    }
    else if (IsKnownUnsupportedRAM(address))
    {
    }
    else
    {
        assert(false && "Unsupported memory write detected!");
    }
}

int32_t MMU::ReadMapROM(uint32_t address)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    int32_t maxNumOfBytesPerEvent = MEMORYSIZES::BYTES_PER_EPAGE * RPGMAKER::MAX_PAGES_PER_EVENT;
    uint16_t eventID = 2 + (address / maxNumOfBytesPerEvent);
    uint16_t pageID = 1 + (address / MEMORYSIZES::BYTES_PER_EPAGE);

    while(pageID > 100)
    {
        pageID /= 100;
    }

    int byteOffsetInEpage = address % MEMORYSIZES::BYTES_PER_EPAGE;

    rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::BYTE_OFFSET_ID), byteOffsetInEpage);
    rpgMaker->CallEvent(lcf::CallEvent::EventType::CONST_MAP_EVENT, eventID, pageID);
    int32_t firstVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_1));
    
    return firstVar; 
}

int32_t MMU::ReadMapRAM(uint32_t address)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // TODO: This needs to be part of the static variables. I need to know how many MAP ROM Events I have!
    const uint16_t mapRAMStart = 3; //TODO: Hardcoded Boot-Rom + One Map ROM for now
    const uint16_t positionIndex = static_cast<uint16_t>(address) / MEMORYSIZES::BYTES_PER_EVENT_POS;

    const int16_t eventIndex = mapRAMStart + positionIndex;
    
    const uint16_t xPos = rpgMaker->ControlVariables_GetEventXPos(eventIndex);
    const uint16_t yPos = rpgMaker->ControlVariables_GetEventYPos(eventIndex);

    // Reconstruct the actual 2-Byte value.
    const int16_t packedValue = xPos + RPGMAKER::MAP_SIZE_X * yPos;
    return packedValue;
}

void MMU::WriteMapRAM(uint32_t address, int32_t value)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // TODO: This needs to be part of the static variables. I need to know how many MAP ROM Events I have!
    const uint16_t mapRAMStart = 3; //TODO: Hardcoded Boot-Rom + One Map ROM for now
    const uint16_t positionIndex = static_cast<uint16_t>(address) / MEMORYSIZES::BYTES_PER_EVENT_POS;

    const int16_t eventIndex = mapRAMStart + positionIndex;

    const uint16_t xPos = value % RPGMAKER::MAP_SIZE_X;
    const uint16_t yPos = value / RPGMAKER::MAP_SIZE_X;

    rpgMaker->ControlVariables_SetEventXPos(eventIndex, xPos);
    rpgMaker->ControlVariables_SetEventYPos(eventIndex, yPos);
}

int32_t MMU::ReadCharaRAM(uint32_t address)
{
    // CharaRAM: [0, 32.768] Bytes
        // <= 2910 Chars
            // EXP: ~10Mio ~ 2^23 >= 2^16 = 2Byte
            // CharData: ~10K ~ 2^13 >= 2^8 = 1Byte
                // 6 Attributes => 6Bytes
            // ItemIds:
                // WeaponID: 2048 = 2^11 >= 2^8 = 1Byte
                // ShieldID: 2048 = 2^11 >= 2^8 = 1Byte
                // BodyID: 2048 = 2^11 >= 2^8 = 1Byte
                // HeadID: 2048 = 2^11 >= 2^8 = 1Byte
                // AccessoryID: 1024 = 2^10 >= 2^8 = 1Byte
                // 5 Slots => 5 Byte
            // Total: 13 Bytes per Char
        // Total: 37.830 Bytes
        // => Need 32kByte / 13Bytes = 2521 Chars.
        // Mapping: 
        // Cartridge RAM: 8Kib, MapRAM[0, 8.191], address[CARTRIDGE_RAM]
        // Banking, up to: 4*8KiB Banks = 32KiB
    // 

    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();
    
    const uint16_t charID = static_cast<uint16_t>(address / MEMORYSIZES::BYTES_PER_CHAR) + 1;
    const uint8_t offset = address % MEMORYSIZES::BYTES_PER_CHAR;

    if(offset >= EXP.first && offset <= EXP.second)
    {
        return rpgMaker->ControlVariables_GetCharEXP(charID);
    }
    else if (offset >= PARAMETERS.first && offset <= PARAMETERS.second)
    {
        lcf::ChangeParam::Parameter parameterType = static_cast<lcf::ChangeParam::Parameter>(offset - PARAMETERS.first);
        return rpgMaker->ControlVariables_GetCharParameter(charID, parameterType);
    }
    else if (offset >= ITEMS.first && offset <= ITEMS.second)
    {
        lcf::ChangeEquip::Item itemType = static_cast<lcf::ChangeEquip::Item>(offset - ITEMS.first);
        return rpgMaker->ControlVariables_GetCharItemID(charID, itemType);
    }

    assert(false && "Unknown Chara RAM address discovered!");
    return 0;
}

void MMU::WriteCharaRAM(uint32_t address, int32_t value)
{
    // CharaRAM: [0, 32.768] Bytes
        // <= 2910 Chars
            // EXP: ~10Mio ~ 2^23 >= 2^16 = 2Byte
            // CharData: ~10K ~ 2^13 >= 2^8 = 1Byte
                // 6 Attributes => 6Bytes
            // ItemIds:
                // WeaponID: 2048 = 2^11 >= 2^8 = 1Byte
                // ShieldID: 2048 = 2^11 >= 2^8 = 1Byte
                // BodyID: 2048 = 2^11 >= 2^8 = 1Byte
                // HeadID: 2048 = 2^11 >= 2^8 = 1Byte
                // AccessoryID: 1024 = 2^10 >= 2^8 = 1Byte
                // 5 Slots => 5 Byte
            // Total: 13 Bytes per Char
        // Total: 37.830 Bytes
        // => Need 32kByte / 13Bytes = 2521 Chars.
        // Mapping: 
        // Cartridge RAM: 8Kib, MapRAM[0, 8.191], address[CARTRIDGE_RAM]
        // Banking, up to: 4*8KiB Banks = 32KiB
    // 

    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();
    
    const uint16_t charID = static_cast<uint16_t>(address / MEMORYSIZES::BYTES_PER_CHAR) + 1;
    const uint8_t offset = address % MEMORYSIZES::BYTES_PER_CHAR;

    if(offset >= EXP.first && offset <= EXP.second)
    {
        rpgMaker->ChangeEXP(charID, value);
        return;
    }
    else if (offset >= PARAMETERS.first && offset <= PARAMETERS.second)
    {
        lcf::ChangeParam::Parameter parameterType = static_cast<lcf::ChangeParam::Parameter>(offset - PARAMETERS.first);
        rpgMaker->ChangeParameters(charID, parameterType, value);
        return;
    }
    else if (offset >= ITEMS.first && offset <= ITEMS.second)
    {
        lcf::ChangeEquip::Item itemType = static_cast<lcf::ChangeEquip::Item>(offset - ITEMS.first);
        rpgMaker->ChangeEquipment(charID, itemType, value);
        return;
    }

    assert(false && "Unknown Chara RAM address discovered!");
}

uint32_t MMU::GBAddressToMapROM(uint16_t address)
{
    const auto* const emuState = EmuState::Get();
    assert(emuState);
    // TODO: Maybe this should a correct size noted somewhere as a constant? BankSize? Where? MMU?, MBC? General GB Constants?
    const uint16_t bankSize = ROM_HIGH.second - ROM_HIGH.first + 1;
    uint32_t MapROMAddress = (address - ROM_LOW.first) % bankSize;

    if(address >= ROM_LOW.first && address <= ROM_LOW.second)
    {
        MapROMAddress += bankSize * emuState->lowRomBankIndex;
        return MapROMAddress;
    }
    else if (address >= ROM_HIGH.first && address <= ROM_HIGH.second)
    {
        MapROMAddress += bankSize * emuState->highRomBankIndex;
        return MapROMAddress;
    }

    assert(false && "Unsupported address given to MapROM!");
    return 0;
}

bool MMU::IsMapROMAddress(uint16_t address)
{
    if(address >= ROM_LOW.first && address <= ROM_LOW.second)
    {
        return true;
    }
    else if (address >= ROM_HIGH.first && address <= ROM_HIGH.second)
    {
        return true;
    }

    return false;
}

uint32_t MMU::GBAddressToMapRAM(uint16_t address)
{
    // MapRAM: [0, 16.800] Bytes
    // Mapping: 
        // VRAM: 8Kib,  MapRAM[0, 8.191], address[VRAM]
        // WRAM: 8Kib,  MapRAM[8.192, 16.383], address[WORK_RAM]
        // OAM: 160B,   MapRAM[16.384, 16.543], address[OAM]
        // IO: 128B,    MapRAM[16.544, 16.671], address[JOYPAD, DISABLE_BOOT_ROM]
        // HRAM: 127B,  MapRAM[16.672, 16.798], address[HRAM]
        // IE: 1B,      MapRAM[16.799, 16.800], address[IE_REGISTER]

    constexpr uint16_t VRAM_SIZE = VRAM.second - VRAM.first + 1;
    constexpr uint16_t WORK_RAM_SIZE = WORK_RAM.second - WORK_RAM.first + 1;
    constexpr uint16_t OAM_SIZE = OAM.second - OAM.first + 1;
    
    if(address >= VRAM.first && address <= VRAM.second)
    {
        return address - VRAM.first;
    }
    // Cartridge RAM between those
    else if (address >= WORK_RAM.first && address <= WORK_RAM.second)
    {
        return address - WORK_RAM.first + VRAM_SIZE;
    }
    // Echo RAM (unused) between those
    else if (address >= OAM.first && address <= OAM.second)
    {
        return address - OAM.first + VRAM_SIZE + WORK_RAM_SIZE;
    }
    // Unused (unused) between those
    else if (address >= JOYPAD.first && address <= IE_REGISTER.second)
    {
        return address - JOYPAD.first + VRAM_SIZE + WORK_RAM_SIZE + OAM_SIZE;
    }

    assert(false && "Unsupported address given to MapRAM!");
    return 0;
}

bool MMU::IsMapRAMAddress(uint16_t address)
{
    // TODO: Kinda copy pasta to the one above, but okay for now.
    // MapRAM: [0, 16.800] Bytes
    // Mapping: 
        // VRAM: 8Kib,  MapRAM[0, 8.191], address[VRAM]
        // WRAM: 8Kib,  MapRAM[8.192, 16.383], address[WORK_RAM]
        // OAM: 160B,   MapRAM[16.384, 16.543], address[OAM]
        // IO: 128B,    MapRAM[16.544, 16.671], address[JOYPAD, DISABLE_BOOT_ROM]
        // HRAM: 127B,  MapRAM[16.672, 16.798], address[HRAM]
        // IE: 1B,      MapRAM[16.799, 16.800], address[IE_REGISTER]
    
    if(address >= VRAM.first && address <= VRAM.second)
    {
        return true;
    }
    // Cartridge RAM between those
    else if (address >= WORK_RAM.first && address <= WORK_RAM.second)
    {
        return true;
    }
    // Echo RAM (unused) between those
    else if (address >= OAM.first && address <= OAM.second)
    {
        return true;
    }
    // Unused (unused) between those
    else if (address >= JOYPAD.first && address <= IE_REGISTER.second)
    {
        return true;
    }

    return false;
}

uint32_t MMU::GBAddressToCharaRAM(uint16_t address)
{
    if(address >= CARTRIDGE_RAM.first && address <= CARTRIDGE_RAM.second)
    {
        const auto* const emuState = EmuState::Get();
        assert(emuState);

        const uint16_t bankSize = CARTRIDGE_RAM.second - CARTRIDGE_RAM.first + 1;
        uint32_t charaRAMAddress = address - CARTRIDGE_RAM.first;
        charaRAMAddress += bankSize * emuState->ramBankIndex;
        return charaRAMAddress;
    }
    
    assert(false && "Unsupported address given to CharaRAM!");
    return 0;
}

bool MMU::IsCharaRAMAddress(uint16_t address)
{
    if(address >= CARTRIDGE_RAM.first && address <= CARTRIDGE_RAM.second)
    {
        return true;
    }

    return false;
}

bool MMU::IsCharaRAMAddressPacked(uint16_t address)
{
    // TODO: A const somewhere else?
    const uint8_t BYTES_PER_CHAR = 13;
    const uint8_t offset = address % BYTES_PER_CHAR;

    if(offset >= EXP.first && offset <= EXP.second)
    {
        return true;
    }

    return false;
}

bool MMU::IsKnownUnsupportedRAM(uint16_t address)
{
    // Echo RAM (unused)
    if (address >= ECHO_RAM.first && address <= ECHO_RAM.second)
    {
        return true;
    }

    // Unused (unused).
    if (address >= UNUSED.first && address <= UNUSED.second)
    {
        return true;
    }

    return false;
}
};