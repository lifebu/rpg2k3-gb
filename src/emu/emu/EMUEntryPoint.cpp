#include "EMUEntryPoint.h"

#include "emu/pch.h"

#include <core/def/VarMapping.h>
#include <core/def/RPGMaker.h>
#include <core/emu_interface/RPGMakerInterface.h>
#include <core/utilities/GBHelper.h>
#include <core/utilities/RPGHelper.h>

#include "emu/memory/MMU.h"
#include "emu/util/DebugUtil.h"

namespace emu 
{

void EMUEntryPoint::RPGMain()
{
    if(!emuState.isInitialized)
    {
        emuState.romBankIndex = 0; // The 2nd ROM bank is accessible.
        emuState.bootRomEnabled = true; // The first 256 Bytes read from the Boot Rom, not the 1st ROM bank.
        // TODO: Setup Input Memory (all to 1).
        // TODO: Set PPU to mode 2.

        emuState.isInitialized = true;
    }

    // Update the MMIO data.

    for(int iCycle = 0; iCycle < CYCLES_PER_FRAME; ++iCycle)
    {
        // Memory Update
        // Timer Updates
        // CPU Cycle
        // PPU Dot
    }


    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // This testcode allows the entire cartridge content to be viewed.

    // Move the view.
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::UP))
    {
        int newOffset = yOffset;
        if(newOffset < 0) newOffset = 0;
        yOffset = newOffset;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::DOWN))
    {
        int newOffset = yOffset ;
        int maxByteOffset = 159 + (143 + newOffset) * 144;

        // Get the size of the ROM.
        const int cartridgeHeaderOffset = 256;
        const int romSizeByteOffset = cartridgeHeaderOffset + 72; // Offset into the CartridgeHeader
        
        int32_t firstVar = MMU::ReadMapROM(romSizeByteOffset);
        std::array<uint8_t, MEMORYSIZES::BYTES_PER_VAR> bytes = unpackVariable(firstVar);
        const int headerRomSize = bytes.at(romSizeByteOffset % 3);

        const int romSizeKByte = ConvertROMSizetoKByte(headerRomSize);

        if(maxByteOffset < romSizeKByte * 1'024)
        {
            yOffset = newOffset;
        }
    }

    PrintROM(yOffset);
}

}; // namespace emu