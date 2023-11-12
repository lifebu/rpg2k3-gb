#include "MMU.h"

#include "emu/pch.h"

#include <core/def/MemorySizes.h>
#include <core/def/VarMapping.h>
#include <core/emu_interface/RPGMakerInterface.h>

namespace emu
{

int32_t MMU::Read(uint32_t byteOffset)
{
    return 0;
}

void MMU::Write(uint32_t bytOffset, int32_t value)
{

}

int32_t MMU::ReadMapROM(uint32_t byteOffset)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    int maxNumOfBytesPerEvent = MEMORYSIZES::BYTES_PER_EPAGE * RPGMAKER::MAX_PAGES_PER_EVENT;
    uint16_t eventID = 2 + (byteOffset / maxNumOfBytesPerEvent);
    uint16_t pageID = 1 + (byteOffset / MEMORYSIZES::BYTES_PER_EPAGE);

    while(pageID > 100)
    {
        pageID /= 100;
    }

    int byteOffsetInEpage = byteOffset % MEMORYSIZES::BYTES_PER_EPAGE;

    rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::BYTE_OFFSET_ID), byteOffsetInEpage);
    rpgMaker->CallEvent(lcf::CallEvent::EventType::CONST_MAP_EVENT, eventID, pageID);
    int32_t firstVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_1));
    
    return firstVar; 
}

void MMU::WriteMapROM(uint32_t byteOffset, int32_t value)
{

}

int32_t MMU::ReadMapRAM(uint32_t byteOffset)
{
    return 0;
}

void MMU::WriteMapRAM(uint32_t byteOffset, int32_t value)
{

}

int32_t MMU::ReadCharaRAM(uint32_t byteOffset)
{
    return 0;
}

void MMU::WriteCharaRAM(uint32_t byteOffset, int32_t value)
{

}

};