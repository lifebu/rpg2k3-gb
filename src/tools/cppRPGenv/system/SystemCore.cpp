#include "SystemCore.h"

#include <iostream>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"

namespace rpgenv
{

SystemCore::SystemCore()
{
    // construct managers.
    rpgenv::InputManager::Get();
    rpgenv::RenderManager::Get();
    rpgenv::LCFManager::Get();
}

static SystemCore* m_Instance = nullptr;

SystemCore* SystemCore::Get() 
{
    if(!m_Instance)
    {
        m_Instance = new SystemCore();
    }
    return m_Instance; 
}

void SystemCore::Init() 
{
    // initialize managers
    auto* inputManager = rpgenv::InputManager::Get();
    auto* renderManager = rpgenv::RenderManager::Get();
    auto* lcfManager = rpgenv::LCFManager::Get();

    inputManager->Init();
    renderManager->Init();
    lcfManager->Init();
}

void SystemCore::Shutdown() 
{
    // shutdown managers
    auto* inputManager = rpgenv::InputManager::Get();
    auto* renderManager = rpgenv::RenderManager::Get();
    auto* lcfManager = rpgenv::LCFManager::Get();

    inputManager->Shutdown();
    renderManager->Shutdown();
    lcfManager->Shutdown();
}

bool SystemCore::ShouldShutdown()
{
    auto* renderManager = rpgenv::RenderManager::Get();

    if(!renderManager->isWindowOpen()) 
    {
        return true;
    }

    return false;
}

void SystemCore::Update()
{
    auto* inputManager = rpgenv::InputManager::Get();
    auto* renderManager = rpgenv::RenderManager::Get();
    auto* lcfManager = rpgenv::LCFManager::Get();

    UpdateEvents();

    switch(m_CurrentState)
    {
        case States::LOADING:
        {
            m_CurrentState = States::RUN_EMU;
        }break;
        case States::RUN_EMU:
        {
            m_Emulator.RPGMain(&m_RPGMakerInterface);
        }break;
        case States::PROCESS_TEXTBOX:
        {

        }break;
        case States::PROCESS_CHOICES:
        {

        }break;
        case States::PROCESS_NUMBER_INPUT:
        {

        }break;
        default:
        {
            static_assert(static_cast<int>(States::STATES_NUM) == 5, "A new system state was added, consider adding a case here!");
        }break;
    }

    RenderManager::Get()->Render();
}

void SystemCore::UpdateEvents()
{
    sf::Window& window = rpgenv::RenderManager::Get()->GetWindow();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

};