#include "MMU.h"

#include "emu/pch.h"

#include <core/def/MemorySizes.h>
#include <core/def/VarMapping.h>
#include <core/emu_interface/RPGMakerInterface.h>
#include <core/utilities/RPGHelper.h>

namespace emu
{

uint8_t MMU::ReadByte(uint16_t address)
{
    // TODO: For MAP RAM: MEMORYSIZES::DMG_RAM_SIZE: 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register

    if(address >= ROM_LOW.first && address <= ROM_LOW.second)
    {
        uint32_t mapROMValue = ReadMapROM(address);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes = unpackVariable(mapROMValue);
        return bytes.at(address % MEMORYSIZES::BYTES_PER_VAR);
    }
    else if (address >= ROM_HIGH.first && address <= ROM_HIGH.second)
    {
        // TODO: We need to calculate the address of the ROM High region to support memory banking (Implement MBC!). I basically need a "local" address here :).
        uint32_t mapROMValue = ReadMapROM(address);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes = unpackVariable(mapROMValue);
        return bytes.at(address % MEMORYSIZES::BYTES_PER_VAR);
    }
    else if(address >= VRAM.first && address <= VRAM.second)
    {
        // TODO: I need to know how the different addresses of different parts of the gameboy (VRAM, WorkRam) actually map to the MapRAM itself. But assuming it starts with VRAM is fine for now.
        uint16_t mapRamAddress = address - VRAM.first;
        uint32_t packedValue = ReadMapRAM(mapRamAddress);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes = unpackMapPosition(packedValue);
        return bytes.at(mapRamAddress % MEMORYSIZES::BYTES_PER_EVENT_POS);
    }

    assert(false && "Unsupported memory read detected!");
    return 0xFF;
}

void MMU::WriteByte(uint16_t address, uint8_t value)
{
    // TODO: For MAP RAM: MEMORYSIZES::DMG_RAM_SIZE: 8KiB VRAM + 8KiB Work Ram + 160B OAM + 128B I/O + 127B High RAM + 1B Interrupt Register

    if(address >= ROM_LOW.first && address <= ROM_LOW.second)
    {
        // This might effect the MBC!
    }
    else if (address >= ROM_HIGH.first && address <= ROM_HIGH.second)
    {
        return; // Cannot Write to high 16kByte of ROM.
    }
    else if (address >= VRAM.first && address <= VRAM.second)
    {
        // TODO: I need to know how the different addresses of different parts of the gameboy (VRAM, WorkRam) actually map to the MapRAM itself. But assuming it starts with VRAM is fine for now.
        uint16_t mapRAMAddress = address - VRAM.first;
        uint32_t packedValue = ReadMapRAM(mapRAMAddress);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_EVENT_POS> bytes = unpackMapPosition(packedValue);
        bytes.at(mapRAMAddress % MEMORYSIZES::BYTES_PER_EVENT_POS) = value;
        packedValue = packMapPosition(bytes);

        WriteMapRAM(mapRAMAddress, packedValue);
        return;
    }

    assert(false && "Unsupported memory write detected!");
    return;
}

int32_t MMU::ReadMapROM(uint16_t address)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    int maxNumOfBytesPerEvent = MEMORYSIZES::BYTES_PER_EPAGE * RPGMAKER::MAX_PAGES_PER_EVENT;
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

int32_t MMU::ReadMapRAM(uint16_t address)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // TODO: This needs to be part of the static variables. I need to know how many MAP ROM Events I have!
    const uint16_t mapRAMStart = 3; //TODO: Hardcoded Boot-Rom + One Map ROM for now
    const uint16_t positionIndex = static_cast<uint16_t>(address) / MEMORYSIZES::BYTES_PER_EVENT_POS;

    const int16_t eventIndex = mapRAMStart + positionIndex / 2;
    
    const uint16_t xPos = rpgMaker->ControlVariables_GetEventXPos(eventIndex);
    const uint16_t yPos = rpgMaker->ControlVariables_GetEventYPos(eventIndex);

    // Reconstruct the actual 2-Byte value.
    const int16_t packedValue = xPos + RPGMAKER::MAP_SIZE_X * yPos;
    return packedValue;
}

void MMU::WriteMapRAM(uint16_t address, int32_t value)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // TODO: This needs to be part of the static variables. I need to know how many MAP ROM Events I have!
    const uint16_t mapRAMStart = 3; //TODO: Hardcoded Boot-Rom + One Map ROM for now
    const uint16_t positionIndex = static_cast<uint16_t>(address) / MEMORYSIZES::BYTES_PER_EVENT_POS;

    const int16_t eventIndex = mapRAMStart + positionIndex / 2;

    const uint16_t xPos = value % RPGMAKER::MAP_SIZE_X;
    const uint16_t yPos = value / RPGMAKER::MAP_SIZE_X;

    rpgMaker->ControlVariables_SetEventXPos(eventIndex, xPos);
    rpgMaker->ControlVariables_SetEventYPos(eventIndex, yPos);
}

int32_t MMU::ReadCharaRAM(uint16_t address)
{
    return 0;
}

void MMU::WriteCharaRAM(uint16_t address, int32_t value)
{

}

};