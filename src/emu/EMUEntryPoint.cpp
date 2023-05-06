#include "EMUEntryPoint.h"

#include "core/def/RPGMaker.h"

namespace emu 
{

void EMUEntryPoint::RPGMain(rpgenv::RPGMakerInterface* rpgMaker)
{
    /*
    rpgMaker->ShowText(
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!");
    */

    rpgMaker->ShowChoices({"Yes", "No", "Maybe?", "Definetly"}, lcf::Choices::ChoiceCaseOnCancel::OWN_BRANCH);

    //rpgMaker->InputNumber(5);
    
    
    return;
}

};