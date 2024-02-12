#include "DebugUtil.h"

#include "emu/pch.h"

#include <core/def/MemorySizes.h>
#include <core/utilities/RPGHelper.h>
#include <core/emu_interface/RPGMakerInterface.h>

#include "emu/memory/MMU.h"

namespace emu
{

void PrintAddressSpace(int yOffset, std::optional<uint8_t> valueOverwrite /*= std::nullopt*/)
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    for(int y = 0; y < 144; ++y)
    {
        for (int x = 0; x < 160; ++x)
        {
            const uint8_t byteValue = 
                valueOverwrite.value_or(MMU::ReadByte(x + (y + yOffset) * 144));
            float r = static_cast<float>(byteValue) / 255.0f;
            float g = static_cast<float>(byteValue) / 255.0f;
            float b = static_cast<float>(byteValue) / 255.0f;

            rpgMaker->ShowPicture(lcf::ShowPicture::PictureIDType::CONSTANT, 0, lcf::ShowPicture::PosType::CONSTANT, x, y, r, g, b);
        }
    }
}
};