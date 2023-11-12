#include "GBHelper.h"

#include "core/pch.h"

uint16_t ConvertROMSizetoKByte(uint8_t romSize)
{
    // TODO: could probably improve this by using romSize = 32 * (header.romSize + 1);
    if (romSize == 0x00) return 32;
    else if (romSize == 0x01) return 64;
    else if (romSize == 0x02) return 128;
    else if (romSize == 0x03) return 256;
    else if (romSize == 0x04) return 512;
    else if (romSize == 0x05) return 1024;
    else if (romSize == 0x06) return 2048;
    else if (romSize == 0x07) return 4096;
    else if (romSize == 0x08) return 8192;
    // Unknown Rom Size
    else assert(false); return 0;
}

uint16_t ConvertRAMSizetoKByte(uint8_t ramSize)
{
    if (ramSize == 0x00) return 0;
    else if (ramSize == 0x02) return 8;
    else if (ramSize == 0x03) return 32;
    else if (ramSize == 0x04) return 128;
    else if (ramSize == 0x05) return 64;
    // Unknown Ram Size
    else assert(false); return 0;
}
