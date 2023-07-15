#pragma once

#include <core/structure/StateMachine.h>

#include <emu/EMUEntryPoint.h>

namespace rpgenv 
{

enum class SystemStates : int
{
    INVALID = -1,

    // At the start the lcf files need to be loaded
    LOADING,
    // The emulator will be updated
    RUN_EMU,
    // Processing a textbox. The emulator will not be updated.
    PROCESS_TEXTBOX,
    // Processing a textbox with different choices. The emulator will not be updated.
    PROCESS_CHOICES,
    // Processing a textbox with a number input. The emulator will not be updated.
    PROCESS_NUMBER_INPUT,

    STATES_NUM
};

class SystemStateMachine : public StateMachine<SystemStates>
{
public:
    SystemStateMachine();

private:
    void UpdateLoadingState();
    void UpdateRunEmuState();
    void UpdateTextboxState();
    void UpdateChoiceState();
    void UpdateInputState();

    emu::EMUEntryPoint m_Emulator;
};

};
