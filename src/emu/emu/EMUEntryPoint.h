#pragma one

#include <core/emu_interface/RPGEntryPoint.h>

#include "emu/def/EmuState.h"

namespace emu 
{

class EMUEntryPoint : public rpgenv::RPGEntryPoint
{
public:
    void RPGMain() override;

private:
    static constexpr int CYCLES_PER_FRAME = 70'224;

    int yOffset = 0;

    EmuState emuState;
};

};