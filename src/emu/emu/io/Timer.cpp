#include "Timer.h"

#include "emu/def/EmuState.h"
#include "emu/memory/MMU.h"
#include "emu/pch.h"

namespace emu
{
void Timer::Init()
{
}

void Timer::CycleUpdate()
{
    const auto* const emuState = EmuState::Get();

    // TODO: Checking like this is honestly super inefficient. Very rarely does this increment.
    // TODO: So maybe not count up, but set the next clock cycle count when an increment will happen?
    // TODO: When all cycles in a frame end, we can subtract them from the times here? So that we support cycles over multiple frames (60Hz).
    // TODO: Maybe divide current cycle count by target and cast it to int. because it casts down it will only be 1 when we have met the cycle count and we will automatically add one to the memory.
    // TODO: Immiedately after that change the target?
    // Divider:
    if(!emuState->isStopped)
    {
        m_DividerCounter++;
        if(m_DividerCounter > m_DividerRate)
        {
            m_DividerCounter = 0;
            // TODO: Seeing this access to MMU Definitions everywhere makes me think that having the memory ranges global in the MMU might not be the best Idea.
            // TODO: Because all systems use the Value from MMU and have their own more specific offsets.
            constexpr uint16_t diffRegisterAddr = MMU::TIMER.first + DIV_REGISTER_OFFSET;
            MMU::WriteByte(diffRegisterAddr, MMU::ReadByte(diffRegisterAddr) + 1);
        }
    }

    // Timer:
    constexpr uint16_t tacRegisterAddr = MMU::TIMER.first + TAC_REGISTER_OFFSET;
    const uint8_t tacRegister = MMU::ReadByte(tacRegisterAddr);
    const bool timerIsEnabled = tacRegister & (1 << TAC_ENABLE_BIT);
    // TODO: This might also be very inefficient to check this super late!
    if(timerIsEnabled)
    {
        const uint8_t timerRateIndex = tacRegister & TAC_CLOCK_MASK;
        const uint32_t timerRate = TIMER_RATE_TABLE[timerRateIndex];
        m_TimerCounter++;
        // TODO: Also super inefficient.
        if(m_TimerCounter > timerRate)
        {
            m_TimerCounter = 0;
            constexpr uint16_t timerRegisterAddr = MMU::TIMER.first + TIMA_REGISTER_OFFSET;
            const uint8_t timerValue = MMU::ReadByte(timerRegisterAddr);
            // TODO: Late decision making.
            const bool wouldOverflow = timerValue == 0xFF;
            if(wouldOverflow)
            {
                constexpr uint16_t timerModuloAddr = MMU::TIMER.first + TMA_REGISTER_OFFSET;
                const uint8_t newTimerValue = MMU::ReadByte(timerModuloAddr);
                MMU::WriteByte(timerRegisterAddr, newTimerValue);
                // TODO: Create an interrupt!
            }
            else
            {
                const uint8_t newTimerValue = timerValue + 1;
                MMU::WriteByte(timerRegisterAddr, newTimerValue);
            }
        }
    }
}


void Timer::ResetDivider()
{
    m_DividerCounter = 0;
}

};
