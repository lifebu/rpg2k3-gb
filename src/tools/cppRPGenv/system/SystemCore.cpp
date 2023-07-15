#include "SystemCore.h"

#include <iostream>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"

namespace rpgenv
{
void SystemCore::Init() 
{
    m_InputManager.Init();
    m_LCFManager.Init();
    m_RenderManager.Init();
    m_SystemStateMachine.Init(SystemStates::LOADING);
}

void SystemCore::Shutdown() 
{
    m_InputManager.Shutdown();
    m_LCFManager.Shutdown();
    m_RenderManager.Shutdown();
}

bool SystemCore::ShouldShutdown()
{
    return !m_RenderManager.isWindowOpen();
}

void SystemCore::Update()
{
    m_RenderManager.PollEvents();
    m_SystemStateMachine.Update();
    m_RenderManager.Render();
}

void SystemCore::ChangeSystemState(SystemStates newState)
{
    m_SystemStateMachine.ChangeState(newState);
}

};