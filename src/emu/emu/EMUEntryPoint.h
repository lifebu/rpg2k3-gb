#pragma one

#include <core/emu_interface/RPGEntryPoint.h>

#include "emu/def/EmuState.h"
#include "emu/memory/MBC.h"

namespace emu 
{

class EMUEntryPoint : public rpgenv::RPGEntryPoint
{
public:
    void RPGMain() override;

private:
    // Initializes the emulator.
    void Initialize();


    // Test function
    void TestPrintMMU();
    void TestMBC();

    static constexpr int CYCLES_PER_FRAME = 70'224;

    int yOffset = 0;

    EmuState emuState;
    MBC mbc;
};

};