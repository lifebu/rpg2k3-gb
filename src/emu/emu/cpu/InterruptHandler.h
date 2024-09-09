#pragma once

#include <utility>

// TODO: Maybe the MMU memory ranges should be defined somewhere else then the MMU itself, to reduce compile time?
#include "emu/memory/MMU.h"

namespace emu
{

// Saving and updating the state of the CPU interrupt system
class InterruptHandler 
{
public:

    // TODO: Maybe this should be an enum? use that in the request interrupt function.
    // Bit offsets into the Interrupt Enable (IE) and Interrupt Flag (IF) register. 
    constexpr static uint8_t VBLANK_INTERRUPT_OFFSET = 0;
    constexpr static uint8_t LCD_INTERRUPT_OFFSET = 1;
    constexpr static uint8_t TIMER_INTERRUPT_OFFSET = 2;
    constexpr static uint8_t SERIAL_INTERRUPT_OFFSET = 3;
    constexpr static uint8_t JOYPAD_INTERRUPT_OFFSET = 4;

    void Init();
    void CycleUpdate();

    // TODO: If you enable interrupts, they should only be active after the next cycle. So if you disable them in the next machine cycle, interrupts will not happen in between them.
    void EnableInterrupts();
    void DisableInterrupts();

    void RequestInterrupt(uint8_t interruptOffset);

private:
    // IME, changed by ei, di and reti instructions. CPU internal, has no address
    bool m_InterruptMasterEnable = false;

    constexpr static uint16_t INTERRUPT_VECTOR_TABLE[] = { 0x40, 0x48, 0x50, 0x58, 0x60 };
};

};