#include "EMUEntryPoint.h"

#include "core/def/RPGMaker.h"

namespace emu 
{

void EMUEntryPoint::RPGMain(rpgenv::RPGMakerInterface* rpgMaker)
{
    /*rpgMaker->ShowText(
        "Emulator is running pretty well I would say so!!!\n"
        "Emulator is running pretty well I would say so!!!\n"
        "Emulator is running pretty well I would say so!!!\n"
        "Emulator is running pretty well I would say so!!!\n");
        */

    rpgMaker->ShowText(
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!"
        "Emulator is running pretty well I would say so!!!");
    
    return;
}

};