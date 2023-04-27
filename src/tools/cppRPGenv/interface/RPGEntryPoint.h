#pragma once

#include "RPGMakerInterface.h"

namespace rpgenv 
{

class RPGEntryPoint
{
    virtual void RPGMain(RPGMakerInterface* rpgMaker) = 0;
};

};