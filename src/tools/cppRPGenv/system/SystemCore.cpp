#include "SystemCore.h"

#include <iostream>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"

namespace rpgenv
{

SystemCore::SystemCore()
{
    m_Managers.emplace_back(std::make_unique<InputManager>());
    m_Managers.emplace_back(std::make_unique<RenderManager>());
    m_Managers.emplace_back(std::make_unique<LCFManager>()); 
}

void SystemCore::Init() 
{
    for(auto& manager : m_Managers)
    {
        manager->Init();
    }
}

void SystemCore::Shutdown() 
{
    for(auto& manager : m_Managers)
    {
        manager->Shutdown();
    }
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
            renderManager->ShowDebugText("Loading...");
            lcfManager->ContinueLoading();
            if(lcfManager->isLoadingFinished())
            {
                renderManager->ShowDebugText("");
                m_CurrentState = States::RUN_EMU;
            }
        }break;
        case States::RUN_EMU:
        {
            m_Emulator.RPGMain();
        }break;
        case States::PROCESS_TEXTBOX:
        {
            UpdateTextboxState();
        }break;
        case States::PROCESS_CHOICES:
        {
            UpdateChoiceState();
        }break;
        case States::PROCESS_NUMBER_INPUT:
        {
            UpdateInputState();
        }break;
        default:
        {
            static_assert(static_cast<int>(States::STATES_NUM) == 5, "A new system state was added, consider adding a case here!");
        }break;
    }

    renderManager->Render();
}

void SystemCore::ChangeSystemState(States newState)
{
    m_CurrentState = newState;
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

void SystemCore::UpdateTextboxState()
{
    auto* inputManager = InputManager::Get();

    if(inputManager->isKeyPressed(RPGMAKER::KeyCodes::CANCEL))
    {
        RenderManager::Get()->CloseTextBox();
        m_CurrentState = States::RUN_EMU;
    }
}

void SystemCore::UpdateChoiceState()
{
    auto* inputManager = InputManager::Get();
    auto* renderManager = RenderManager::Get();
    
    if(inputManager->isKeyPressed(RPGMAKER::KeyCodes::UP))
    {
        renderManager->MoveChoice(-1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::DOWN))
    {
        renderManager->MoveChoice(1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::CANCEL))
    {
        if(renderManager->ClosingChoiceAllowed())
        {
            int choiceIndex = renderManager->CancelChoice();
            m_CurrentState = States::RUN_EMU;
        }
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::SELECT))
    {
        int choiceIndex = renderManager->CloseChoice();
        m_CurrentState = States::RUN_EMU;
    }
}

void SystemCore::UpdateInputState()
{
    auto* inputManager = InputManager::Get();
    auto* renderManager = RenderManager::Get();
    
    if(inputManager->isKeyPressed(RPGMAKER::KeyCodes::UP))
    {
        renderManager->ChangeSelectedNumber(1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::DOWN))
    {
        renderManager->ChangeSelectedNumber(-1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::LEFT))
    {
        renderManager->MoveSelectedNumber(-1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::RIGHT))
    {
        renderManager->MoveSelectedNumber(1);
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::SELECT))
    {
        int Chosennumber = renderManager->CloseNumberInput();
        m_CurrentState = States::RUN_EMU;
    }
}

};