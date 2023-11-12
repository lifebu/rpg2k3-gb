#pragma once

#include <utility>

namespace emu
{

// TODO: To improve performance I could use a cache.
    // I will probably have a lot of variables that I technically don't use.
    // 1024 Variables (for example) can be used to store the last 1024 byte values that were read/written.
    // For read this is way faster, for writes, this would mean, that I need to repack the variables when I evict them from the cache?
    // This only helps if I mostly have local memory accesspatterns.
    // Similar to a TLB (MAC ~ Memory Access Cache)?
    // Packing/Unpacking all the time is expensive :O
class MMU
{
public:
    // GB Memory Map:
    // ROM
    constexpr static std::pair<uint16_t, uint16_t> ROM_LOW = 
                                    std::make_pair(0x0000, 0x3FFF);
    constexpr static std::pair<uint16_t, uint16_t> ROM_HIGH = 
                                    std::make_pair(0x4000, 0x7FFF);

    // Boot ROM (hides ROM, only relevant when activated).
    constexpr static std::pair<uint16_t, uint16_t> BOOT_ROM = 
                                    std::make_pair(0x0000, 0x0100);

    // RST Vectors
    constexpr static std::pair<uint16_t, uint16_t> RST_1 =
                                    std::make_pair(0x0000, 0x0004);
    constexpr static std::pair<uint16_t, uint16_t> RST_2 =
                                    std::make_pair(0x0008, 0x000C);
    constexpr static std::pair<uint16_t, uint16_t> RST_3 = 
                                    std::make_pair(0x0010, 0x0014);
    constexpr static std::pair<uint16_t, uint16_t> RST_4 = 
                                    std::make_pair(0x0018, 0x001C);
    constexpr static std::pair<uint16_t, uint16_t> RST_5 = 
                                    std::make_pair(0x0020, 0x0024);
    constexpr static std::pair<uint16_t, uint16_t> RST_6 = 
                                    std::make_pair(0x0028, 0x002C);
    constexpr static std::pair<uint16_t, uint16_t> RST_7 = 
                                    std::make_pair(0x0030, 0x0034);
    constexpr static std::pair<uint16_t, uint16_t> RST_8 = 
                                    std::make_pair(0x0038, 0x003C);

    // Interrupt Vectors
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_VBLANK = 
                                    std::make_pair(0x0040, 0x0044);
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_STAT = 
                                    std::make_pair(0x0048, 0x004C);
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_TIMER = 
                                    std::make_pair(0x0050, 0x0054);
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_SERIAL = 
                                    std::make_pair(0x0058, 0x005C);
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_JOYPAD = 
                                    std::make_pair(0x0060, 0x0064);

    // VRAM
    constexpr static std::pair<uint16_t, uint16_t> VRAM = 
                                    std::make_pair(0x8000, 0x9FFF);

    // Cartridge RAM
    constexpr static std::pair<uint16_t, uint16_t> CARTRIDGE_RAM = 
                                    std::make_pair(0xA000, 0xBFFF);

    // Work RAM
    constexpr static std::pair<uint16_t, uint16_t> WORK_RAM = 
                                    std::make_pair(0xC000, 0xDFFF);
    
    // Echo RAM (unused)
    constexpr static std::pair<uint16_t, uint16_t> ECHO_RAM = 
                                    std::make_pair(0xE000, 0xFDFF);

    // OAM
    constexpr static std::pair<uint16_t, uint16_t> OAM = 
                                    std::make_pair(0xFE00, 0xFE9F);

    // Unused (unused)
    constexpr static std::pair<uint16_t, uint16_t> UNUSED = 
                                    std::make_pair(0xFEA0, 0xFEFF);

    // I/O
    constexpr static std::pair<uint16_t, uint16_t> JOYPAD = 
                                    std::make_pair(0xFF00, 0xFF00);
    constexpr static std::pair<uint16_t, uint16_t> SERIAL = 
                                    std::make_pair(0xFF01, 0xFF02);
    constexpr static std::pair<uint16_t, uint16_t> TIMER = 
                                    std::make_pair(0xFF04, 0xFF07);
    constexpr static std::pair<uint16_t, uint16_t> AUDIO = 
                                    std::make_pair(0xFF10, 0xFF26);
    constexpr static std::pair<uint16_t, uint16_t> INTERRUPT_FLAG = 
                                    std::make_pair(0xFF0F, 0xFF0F);
    constexpr static std::pair<uint16_t, uint16_t> WAVE = 
                                    std::make_pair(0xFF30, 0xFF3F);
    constexpr static std::pair<uint16_t, uint16_t> LCD = 
                                    std::make_pair(0xFF40, 0xFF4B);
    constexpr static std::pair<uint16_t, uint16_t> DISABLE_BOOT_ROM = 
                                    std::make_pair(0xFF50, 0xFF50);

    // HRAM
    constexpr static std::pair<uint16_t, uint16_t> HRAM = 
                                    std::make_pair(0xFF80, 0xFFFE);

    // IE Register
    constexpr static std::pair<uint16_t, uint16_t> IE_REGISTER = 
                                    std::make_pair(0xFFFF, 0xFFFF);

////////////////////////////////////////////////////////////////////////////////////////////////////

    // Memory Access:
    // Read/Write memory from the 16-Bit GB address space. Will redirect to the correct ROM/RAM in RPG Maker.
    static uint8_t  ReadByte(uint16_t address);
    static void     WriteByte(uint16_t address, uint8_t value);

private:
    // Read MapROM: Used for Cartridge ROM.
    static int32_t  ReadMapROM(uint32_t address);

    // Read/Write MapRAM: Used for WorkRAM, VRAM, OAM
    static int32_t  ReadMapRAM(uint32_t address);
    static void     WriteMapRAM(uint32_t address, int32_t value);

    // Read/Write CharaRAM: Used for Cartridge RAM.
    static int32_t  ReadCharaRAM(uint32_t address);
    static void     WriteCharaRAM(uint32_t address, int32_t value);

    // RPG Maker Address Mapping:
    static uint32_t GBAddressToMapRAM(uint16_t address);
    static bool IsMapRAMAddress(uint16_t address);

    static uint32_t GBAddressToMapROM(uint16_t address);
    static bool IsMapROMAddress(uint16_t address);
};

};