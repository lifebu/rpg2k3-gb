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
        mbc.Init();
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

    // TODO: Testcode for the MBC!
    /*
    MMU::WriteByte(0x0000, 0xA); // Enable RAM
    MMU::WriteByte(0x0000, 0x0); // Disable RAM
    // Select different ROM Banks:
    MMU::WriteByte(0x2000, 0);
    assert(emuState.highRomBankIndex == 1);
    MMU::WriteByte(0x2000, 1);
    assert(emuState.highRomBankIndex == 1);
    MMU::WriteByte(0x2000, 2);
    assert(emuState.highRomBankIndex == 2);
    MMU::WriteByte(0x2000, 7);
    assert(emuState.highRomBankIndex == 7);
    MMU::WriteByte(0x2000, 8);
    assert(emuState.highRomBankIndex == 1);
    */


    // This testcode allows the entire address space to be viewed.
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // Move the view.
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::UP))
    {
        int newOffset = yOffset - 1;
        if(newOffset < 0) newOffset = 0;
        yOffset = newOffset;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::DOWN))
    {
        int newOffset = yOffset + 1;
        int maxByteOffset = 159 + (143 + newOffset) * 144;

        if(maxByteOffset < MEMORYSIZES::ADDRESS_SPACE_SIZE)
        {
            yOffset = newOffset;
        }
    }

    // Change ROM Mapping
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::SHIFT))
    {
        const int newBankIndex = emuState.highRomBankIndex + 1;

        // Get the size of the ROM.
        const int cartridgeHeaderOffset = 256;
        const int romSizeByteOffset = cartridgeHeaderOffset + 72; // Offset into the CartridgeHeader
        
        uint8_t headerRomSize = MMU::ReadByte(romSizeByteOffset);
        const int romSizeKByte = ConvertROMSizetoKByte(headerRomSize);
        const int numBanks = (romSizeKByte / 16); // Each Bank has 16kByte
        emuState.highRomBankIndex = newBankIndex % (numBanks - 1);
    }

    // Change RAM Mapping
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::SELECT))
    {
        const int newBankIndex = emuState.ramBankIndex + 1;

        // Get the size of the RAM.
        const int cartridgeHeaderOffset = 256;
        const int ramSizeByteOffset = cartridgeHeaderOffset + 73; // Offset into the CartridgeHeader
        
        uint8_t headerRamSize = MMU::ReadByte(ramSizeByteOffset);
        const int ramSizeKByte = ConvertRAMSizetoKByte(headerRamSize);
        const int numBanks = (ramSizeKByte / 8); // Each Bank has 8kByte
        emuState.ramBankIndex = newBankIndex % (numBanks - 1);
    }

    PrintAddressSpace(yOffset);
}

}; // namespace emu