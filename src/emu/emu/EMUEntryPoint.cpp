#include "EMUEntryPoint.h"

#include <algorithm>

#include "core/def/VarMapping.h"
#include "core/def/RPGMaker.h"
#include "core/emu_interface/RPGMakerInterface.h"
#include "core/utilities/RPGHelper.h"

namespace emu 
{

void EMUEntryPoint::RPGMain()
{
    auto* rpgMaker = rpgenv::RPGMakerInterface::Get();

    // This testcode allows the entire cartridge content to be viewed.

    // Get the size of the ROM.
    const int cartridgeHeaderOffset = 256;
    const int romSizeByteOffset = cartridgeHeaderOffset + 72; // Offset into the CartridgeHeader
    rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::BYTE_OFFSET_ID), romSizeByteOffset);
    rpgMaker->CallEvent(lcf::CallEvent::EventType::CONST_MAP_EVENT, 2, 1);
    int32_t firstVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_1));
    std::vector<uint8_t> bytes = unpackVariable(firstVar);
    const int headerRomSize = bytes.at(romSizeByteOffset % 3);

    int romSizeKByte = 0;
    if (headerRomSize == 0x00)      romSizeKByte = 32;
    else if (headerRomSize == 0x01) romSizeKByte = 64;
    else if (headerRomSize == 0x02) romSizeKByte = 128;
    else if (headerRomSize == 0x03) romSizeKByte = 256;
    else if (headerRomSize == 0x04) romSizeKByte = 512;
    else if (headerRomSize == 0x05) romSizeKByte = 1'024;
    else if (headerRomSize == 0x06) romSizeKByte = 2'048;
    else if (headerRomSize == 0x07) romSizeKByte = 4'096;
    else if (headerRomSize == 0x08) romSizeKByte = 8'192;

    // Change speed.
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::SYMBOL_PLUS)) 
    {
        speed++;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::SYMBOL_MINUS)) 
    {
        speed--;
        if(speed < 1) speed = 1;
    }

    // Move the view.
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::UP))
    {
        int newOffset = yOffset - speed;
        if(newOffset < 0) newOffset = 0;
        yOffset = newOffset;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::DOWN))
    {
        int newOffset = yOffset + speed;
        int maxByteOffset = 159 + (143 + newOffset) * 144;

        if(maxByteOffset < romSizeKByte * 1'024)
        {
            yOffset = newOffset;
        }
    }

    // Splat rom data.
    for(int y = 0; y < 144; ++y)
    {
        for (int x = 0; x < 160; ++x)
        {
            int byteOffset = x + (y + yOffset) * 144;
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
            int32_t secondVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_2));
            std::vector<uint8_t> bytes = unpackVariable(firstVar);

            int byteIndex = byteOffset % 3;
            float r = (float)bytes.at(byteIndex) / 255.0f;
            float g = (float)bytes.at(byteIndex) / 255.0f;
            float b = (float)bytes.at(byteIndex) / 255.0f;

            rpgMaker->ShowPicture(lcf::ShowPicture::PictureIDType::CONSTANT, 0, lcf::ShowPicture::PosType::CONSTANT, x, y, r, g, b);
        }
    }

    return;
}


}; // namespace emu