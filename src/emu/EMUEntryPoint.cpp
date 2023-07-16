#include "EMUEntryPoint.h"

#include <algorithm>

#include "core/def/RPGMaker.h"
#include "core/emu_interface/RPGMakerInterface.h"

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


    x = std::clamp(x, 0, 160 - 1);
    y = std::clamp(y, 0, 144 - 1);

    rpgMaker->ShowPicture(lcf::ShowPicture::PictureIDType::CONSTANT, 0, lcf::ShowPicture::PosType::CONSTANT, x, y, 0.5f, 0.5f, 0.5f);
    
    
    return;
}


}; // namespace emu