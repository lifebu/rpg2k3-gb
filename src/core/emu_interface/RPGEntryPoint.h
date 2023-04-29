#pragma once

#include "RPGMakerInterface.h"

namespace rpgenv 
{

class RPGEntryPoint
{
public:
    virtual void RPGMain(RPGMakerInterface* rpgMaker) = 0;
};

};