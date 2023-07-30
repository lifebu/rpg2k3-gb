#pragma once

#include <core/structure/Logger.h>
#include <core/structure/Singleton.h>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"
#include "manager/VariableManager.h"
#include "manager/structure/ManagerInterface.h"
#include "system/SystemStateMachine.h"
#include "interface_impl/RPGMakerImpl.h"

namespace rpgenv 
{


// Responsible for manager / interface lifetime, entrypoint, and core loop.
class SystemCore : public Singleton<SystemCore>, public IManager
{
public:
    void Init() override;
    void Shutdown() override;
    void Update() override;

    bool ShouldShutdown();
   
    void ChangeSystemState(SystemStates newState);

private:
    Logger         m_Logger;
    InputManager   m_InputManager;
    LCFManager     m_LCFManager;
    RenderManager  m_RenderManager; 
    VariableManager m_VariableManager;
    rpgenv::RPGMakerImpl m_RPGMakerInterface;

    SystemStateMachine m_SystemStateMachine;
};

};