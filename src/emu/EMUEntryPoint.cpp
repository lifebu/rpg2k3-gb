#include "EMUEntryPoint.h"

namespace emu 
{

void EMUEntryPoint::RPGMain(rpgenv::RPGMakerInterface* rpgMaker)
{
    rpgMaker->CallEvent();
}

};