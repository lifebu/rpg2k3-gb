#include "InterruptHandler.h"

#include "emu/pch.h"

namespace emu
{

void InterruptHandler::Init()
{
}

void InterruptHandler::CycleUpdate() 
{
    if(!m_InterruptMasterEnable)
        return;

    uint8_t interruptFlag = MMU::ReadByte(MMU::INTERRUPT_FLAG.first);
    const uint8_t interruptEnable = MMU::ReadByte(MMU::IE_REGISTER.first);
    uint8_t interruptsToHandle = interruptFlag & interruptEnable;
    
    for(int iInterrupt = 0; iInterrupt < 5; ++iInterrupt)
    {
        const bool shouldHandle = interruptsToHandle & 0b1;
        interruptsToHandle >>= 1;

        if(shouldHandle)
        {
            // Reset IF and IME
            interruptFlag = interruptFlag & !(1 << iInterrupt);
            MMU::WriteByte(MMU::INTERRUPT_FLAG.first, interruptFlag);
            m_InterruptMasterEnable = false;

            const uint16_t interruptAddr = INTERRUPT_VECTOR_TABLE[iInterrupt];

            // TODO: This needs to take a couple of cycles!
            // Wait 2 MCycles, Push PC on Stack (2 MCycles), Set PC to Address of handler (1 MCycle).
            break;
        }

        // TODO: Interrupt handlers should call reti (return interrupt)
            // This will set the IME to true, and pop the return address from stack to PC.
    }
}

void InterruptHandler::EnableInterrupts()
{
    m_InterruptMasterEnable = true;
}

void InterruptHandler::DisableInterrupts() 
{
    m_InterruptMasterEnable = false;
}

void InterruptHandler::RequestInterrupt(uint8_t interruptOffset) 
{
    uint8_t interruptFlag = MMU::ReadByte(MMU::INTERRUPT_FLAG.first);
    uint8_t result = interruptFlag | (1 << interruptOffset); // set flag to true.
    MMU::WriteByte(MMU::INTERRUPT_FLAG.first, result);
}

}; // namespace emu
