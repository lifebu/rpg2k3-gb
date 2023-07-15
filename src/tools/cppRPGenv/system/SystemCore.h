#pragma once

#include <memory>

#include <core/structure/Singleton.h>

#include <emu/EMUEntryPoint.h>

#include "manager/structure/ManagerInterface.h"
#include "interface_impl/RPGMakerImpl.h"

namespace rpgenv 
{


// Responsible for manager lifetime, entrypoint, and core loop.
class SystemCore : public Singleton<SystemCore>, public IManager
{
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

    SystemCore();

    void Init() override;
    void Shutdown() override;
    void Update() override;

    bool ShouldShutdown();
   
    void ChangeSystemState(States newState);

private:
    void UpdateEvents();
    void UpdateTextboxState();
    void UpdateChoiceState();
    void UpdateInputState();

    std::vector<std::unique_ptr<IManager>> m_Managers;

    States m_CurrentState;
    emu::EMUEntryPoint m_Emulator;
    rpgenv::RPGMakerImpl m_RPGMakerInterface;
};

};