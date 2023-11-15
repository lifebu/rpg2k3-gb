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

    // MMU Testcode.
    // TODO: Test this some more. I get the unpacked second value, and not the one I expect.
    /*
    MMU::WriteByte(MMU::VRAM.first, 60);
    uint8_t redByte = MMU::ReadByte(MMU::VRAM.first);
    MMU::WriteByte(MMU::VRAM.first + 1, 62);
    redByte = MMU::ReadByte(MMU::VRAM.first);
    redByte = MMU::ReadByte(MMU::VRAM.first + 1);
    MMU::WriteByte(MMU::VRAM.first + 2, 63);
    redByte = MMU::ReadByte(MMU::VRAM.first);
    redByte = MMU::ReadByte(MMU::VRAM.first + 1);
    redByte = MMU::ReadByte(MMU::VRAM.first + 2);

    MMU::WriteByte(MMU::WORK_RAM.first, 14);
    MMU::WriteByte(MMU::OAM.first, 15);
    MMU::WriteByte(MMU::IE_REGISTER.first, 16);
    */

    // This testcode allows the entire cartridge content to be viewed.
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
        const int newBankIndex = emuState.romBankIndex + 1;

        // Get the size of the ROM.
        const int cartridgeHeaderOffset = 256;
        const int romSizeByteOffset = cartridgeHeaderOffset + 72; // Offset into the CartridgeHeader
        
        uint8_t headerRomSize = MMU::ReadByte(romSizeByteOffset);
        const int romSizeKByte = ConvertROMSizetoKByte(headerRomSize);
        const int numBanks = (romSizeKByte / 16) - 2; // Each Bank has 16kByte and the Index = 0 is for the 2nd 16kByte in the ROM.

        // Wrap around the Banks
        if(newBankIndex > numBanks)
        {
            emuState.romBankIndex = 0;
        }
        else
        {
            emuState.romBankIndex = newBankIndex;
        }
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
        const int numBanks = (ramSizeKByte / 8) - 1; // Each Bank has 8kByte and the Index = 0 is for the 2nd 16kByte in the ROM.

        // Wrap around the Banks
        if(newBankIndex > numBanks)
        {
            emuState.ramBankIndex = 0;
        }
        else
        {
            emuState.ramBankIndex = newBankIndex;
        }
    }

    PrintAddressSpace(yOffset);
}

}; // namespace emu