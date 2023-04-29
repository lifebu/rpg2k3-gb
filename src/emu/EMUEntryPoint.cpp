#include "EMUEntryPoint.h"

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
}

};