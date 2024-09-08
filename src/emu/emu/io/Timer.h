#pragma once

#include <utility>

namespace emu
{

// Responsible for updating the Timer and Divider.
class Timer 
{
public:
    // Register Offsets:
    constexpr static uint8_t DIV_REGISTER_OFFSET  = 0;
    constexpr static uint8_t TIMA_REGISTER_OFFSET = 1;
    constexpr static uint8_t TMA_REGISTER_OFFSET  = 2;
    constexpr static uint8_t TAC_REGISTER_OFFSET  = 3;

    // TAC:
    // TODO: Should I save these specific bits as bit indices or directly as a mask here? How are the usually used?
    // TODO: If I use the mask, then I can also use this to have "multi-bit" masks (like the CLOCK_MASK).
    // TODO: I think they are always used to create masks.
    constexpr static uint8_t TAC_ENABLE_BIT = 2;
    constexpr static uint8_t TAC_CLOCK_MASK = 0x03;

    void Init();
    void CycleUpdate();

    // TODO: Call this when the cpu is set to stop mode.
    void ResetDivider();

private:
    // Divider:
    int m_DividerCounter = 0;
    const int m_DividerRate = 16'384; // when divider is incremented.

    // Timer:
    constexpr static uint32_t TIMER_RATE_TABLE[] = { 4'096, 262'144, 65'536, 16'384 };
    int m_TimerCounter = 0; 
};

};