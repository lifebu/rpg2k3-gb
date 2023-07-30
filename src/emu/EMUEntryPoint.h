#pragma one

#include "core/emu_interface/RPGEntryPoint.h"

namespace emu 
{

class EMUEntryPoint : public rpgenv::RPGEntryPoint
{
public:
    void RPGMain() override;

private:
    int yOffset = 0;
};

};