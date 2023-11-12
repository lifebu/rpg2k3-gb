#pragma once

#include <cstdint>

// Convert ROM size found in header into KByte.
uint16_t ConvertROMSizetoKByte(uint8_t romSize);

// Convert RAM size found in header into KByte.
uint16_t ConvertRAMSizetoKByte(uint8_t ramSize);