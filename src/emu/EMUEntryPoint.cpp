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

    if(!done)
    {
        for(int y = 0; y < 144; ++y)
        {
            for (int x = 0; x < 160; ++x)
            {
                int byteOffset = x + y * 144;
                int maxNumOfBytesPerEvent = MEMORYSIZES::BYTES_PER_EPAGE * RPGMAKER::MAX_PAGES_PER_EVENT;
                uint16_t eventID = 2 + (byteOffset / maxNumOfBytesPerEvent);
                uint16_t pageID = 1 + (byteOffset / MEMORYSIZES::BYTES_PER_EPAGE);

                int byteOffsetInEpage = byteOffset % MEMORYSIZES::BYTES_PER_EPAGE;

                rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::BYTE_OFFSET_ID), byteOffsetInEpage);
                rpgMaker->CallEvent(lcf::CallEvent::EventType::CONST_MAP_EVENT, eventID, pageID);
                int32_t firstVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_1));
                int32_t secondVar = rpgMaker->ControlVariables(static_cast<uint16_t>(VARMAPPING::READ_VAR_2));
                std::vector<uint8_t> bytes = unpackVariable(firstVar);

                rpgMaker->ShowPicture(lcf::ShowPicture::PictureIDType::CONSTANT, 0, lcf::ShowPicture::PosType::CONSTANT, x, y, 
                    (float)bytes.at(0) / 255.0f, 
                    (float)bytes.at(1) / 255.0f, 
                    (float)bytes.at(2) / 255.0f);
            }
        }
    }

    done = true;
    return;
}


}; // namespace emu