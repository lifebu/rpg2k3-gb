#pragma once

namespace rpgenv
{

class IManager
{
public:
    virtual void Init() {};
    virtual void Shutdown() {};
    virtual void Update() {};
};

};