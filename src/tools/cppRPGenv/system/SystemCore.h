#pragma once

#include <memory>

#include <core/structure/Singleton.h>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"
#include "manager/structure/ManagerInterface.h"
#include "system/SystemStateMachine.h"
#include "interface_impl/RPGMakerImpl.h"

namespace rpgenv 
{


// Responsible for manager / interface lifetime, entrypoint, and core loop.
class SystemCore : public Singleton<SystemCore>, public IManager
{
public:
    SystemCore();

    void Init() override;
    void Shutdown() override;
    void Update() override;

    bool ShouldShutdown();
   
    void ChangeSystemState(SystemStates newState);

private:
    std::unique_ptr<InputManager>   m_InputManager;
    std::unique_ptr<LCFManager>     m_LCFManager;
    std::unique_ptr<RenderManager>  m_RenderManager;
    
    std::unique_ptr<rpgenv::RPGMakerImpl> m_RPGMakerInterface;

    SystemStateMachine m_SystemStateMachine;
};

};