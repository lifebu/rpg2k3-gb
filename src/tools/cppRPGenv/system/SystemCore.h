#pragma once

#include <emu/EMUEntryPoint.h>

#include "interface_impl/RPGMakerImpl.h"

namespace rpgenv 
{

// 
class SystemCore
{
    SystemCore();

public:
    enum class States : int
    {
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


    static SystemCore* Get();

    void Init();
    void Shutdown();

    bool ShouldShutdown();
    void Update();

    void ChangeSystemState(States newState);

private:
    void UpdateEvents();
    void UpdateTextboxState();
    void UpdateChoiceState();
    void UpdateInputState();

    States m_CurrentState;
    emu::EMUEntryPoint m_Emulator;
    rpgenv::RPGMakerImpl m_RPGMakerInterface;
};

};