#include "SystemCore.h"

#include <iostream>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"

namespace rpgenv
{

SystemCore::SystemCore()
    : m_InputManager(std::make_unique<InputManager>()),
      m_LCFManager(std::make_unique<LCFManager>()),
      m_RenderManager(std::make_unique<RenderManager>()),
      m_RPGMakerInterface(std::make_unique<rpgenv::RPGMakerImpl>())
{}

void SystemCore::Init() 
{
    m_InputManager->Init();
    m_LCFManager->Init();
    m_RenderManager->Init();
}

void SystemCore::Shutdown() 
{
    m_InputManager->Shutdown();
    m_LCFManager->Shutdown();
    m_RenderManager->Shutdown();
}

bool SystemCore::ShouldShutdown()
{
    auto* renderManager = rpgenv::RenderManager::Get();
    return !renderManager->isWindowOpen();
}

void SystemCore::Update()
{
    auto* renderManager = RenderManager::Get();
    renderManager->PollEvents();

    m_SystemStateMachine.Update();

    renderManager->Render();
}

void SystemCore::ChangeSystemState(SystemStates newState)
{
    m_SystemStateMachine.ChangeState(newState);
}

};