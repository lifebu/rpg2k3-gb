#pragma once

namespace emu
{

class MMU
{
public:
    // Special Memory:
    // I/O
    constexpr static uint16_t JOYPAD_START =               0xFF00;
    constexpr static uint16_t JOYPAD_END =                 0xFF00;
    constexpr static uint16_t SERIAL_START =               0xFF01;
    constexpr static uint16_t SERIAL_END =                 0xFF02;
    constexpr static uint16_t TIMER_START =                0xFF04;
    constexpr static uint16_t TIMER_END =                  0xFF07;

    constexpr static uint16_t DISABLE_BOOT_ROM_START =     0xFF50;
    constexpr static uint16_t DISABLE_BOOT_ROM_END =       0xFF50;

    static int32_t Read(uint32_t byteOffset);
    static void Write(uint32_t bytOffset, int32_t value);

    static int32_t ReadMapROM(uint32_t byteOffset);
    static void WriteMapROM(uint32_t byteOffset, int32_t value);

    static int32_t ReadMapRAM(uint32_t byteOffset);
    static void WriteMapRAM(uint32_t byteOffset, int32_t value);

    static int32_t ReadCharaRAM(uint32_t byteOffset);
    static void WriteCharaRAM(uint32_t byteOffset, int32_t value);
};

};