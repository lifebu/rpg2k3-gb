#pragma one

#include "core/emu_interface/RPGEntryPoint.h"

namespace emu 
{

class EMUEntryPoint : public rpgenv::RPGEntryPoint
{
public:
    void RPGMain() override;

private:
    int x = 0;
    int y = 0;
    int done = false;
};

};