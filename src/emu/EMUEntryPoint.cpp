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

    /*
    rpgMaker->ShowText(
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!");
    */

    //rpgMaker->ShowChoices({"Yes", "No", "Maybe?", "Definetly"}, lcf::Choices::ChoiceCaseOnCancel::OWN_BRANCH);

    
    //rpgMaker->InputNumber(5);
    /*
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::UP))
    {
        y--;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::DOWN))
    {
        y++;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::LEFT))
    {
        x--;
    }
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::RIGHT))
    {
        x++;
    }
    */

    //x = std::clamp(x, 0, 160 - 1);
    //y = std::clamp(y, 0, 144 - 1);

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
        // TODO: This should use the actual ROM-Size.
        if(maxByteOffset < 32'768)
        {
            yOffset = newOffset;
        }
    }

    // splat rom data.
    for(int y = 0; y < 144; ++y)
    {
        for (int x = 0; x < 160; ++x)
        {
            int byteOffset = x + (y + yOffset) * 144;
            int maxNumOfBytesPerEvent = MEMORYSIZES::BYTES_PER_EPAGE * RPGMAKER::MAX_PAGES_PER_EVENT;
            uint16_t eventID = 2 + (byteOffset / maxNumOfBytesPerEvent);
            uint16_t pageID = 1 + (byteOffset / MEMORYSIZES::BYTES_PER_EPAGE);

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