#pragma once

#include <core/structure/Singleton.h>
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
    // An error was detected and we abort.
    GB_PANIC,

    STATES_NUM
};

// Responsible for the System states and most of the logic glueing everything else together.
class SystemStateMachine : public StateMachine<SystemStates>, public Singleton<SystemStateMachine>
{
public:
    SystemStateMachine();

private:
    // State Transitions

    // State Functions
    void UpdateAnyState();
    void UpdateLoadingState();
    void UpdateRunEmuState();
    void UpdateTextboxState();
    void UpdateChoiceState();
    void UpdateInputState();

    emu::EMUEntryPoint m_Emulator;
};

};
