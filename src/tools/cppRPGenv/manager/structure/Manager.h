#pragma once

#include <string>
#include <vector>

#include "core/def/RPGMaker.h"
#include "core/lcf/event/EventCommandFactoryDef.h"
#include "core/structure/Singleton.h"

namespace rpgenv
{

template <class T>
class Manager : public Singleton<T>
{
public:
    virtual void Init() {};
    virtual void Shutdown() {};
};

};