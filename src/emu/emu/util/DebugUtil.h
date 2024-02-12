#pragma once

#include <optional>

namespace emu
{
    // prints the address space to the screen starting from a row offset
    // optional allows to overwrite all the values with a single one in order to view a specific value in memory.
    void PrintAddressSpace(int yOffset, std::optional<uint8_t> valueOverwrite = std::nullopt);
};