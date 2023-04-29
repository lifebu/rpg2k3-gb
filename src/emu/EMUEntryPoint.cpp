#include "EMUEntryPoint.h"

#include "core/def/RPGMaker.h"

namespace emu 
{

void EMUEntryPoint::RPGMain(rpgenv::RPGMakerInterface* rpgMaker)
{
    static int once = 0;
    if(once < 1)
    {
        rpgMaker->DebugPrint("Emulator is running!");
        once ++;
    }

    static int xPos = 0;
    
    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::LEFT))
    {
        xPos--;
    }

    if(rpgMaker->KeyInputProcessing(RPGMAKER::KeyCodes::RIGHT))
    {
        xPos++;
    }
}

};