#include "SystemStateMachine.h"

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"

namespace rpgenv
{

SystemStateMachine::SystemStateMachine() 
{
    AddUpdateFunction(SystemStates::LOADING,                [this](){ UpdateLoadingState(); });
    AddUpdateFunction(SystemStates::RUN_EMU,                [this](){ UpdateRunEmuState(); });
    AddUpdateFunction(SystemStates::PROCESS_TEXTBOX,        [this](){ UpdateTextboxState(); });
    AddUpdateFunction(SystemStates::PROCESS_CHOICES,        [this](){ UpdateChoiceState(); });
    AddUpdateFunction(SystemStates::PROCESS_NUMBER_INPUT,   [this](){ UpdateInputState(); });
}

void SystemStateMachine::UpdateLoadingState() 
{
    auto* renderManager = rpgenv::RenderManager::Get();
    auto* lcfManager = rpgenv::LCFManager::Get();

    renderManager->ShowDebugText("Loading...");
    lcfManager->ContinueLoading();
    if(lcfManager->isLoadingFinished())
    {
        renderManager->ShowDebugText("");
        ChangeState(SystemStates::RUN_EMU);
    }
}

void SystemStateMachine::UpdateRunEmuState() 
{
    m_Emulator.RPGMain();
}

void SystemStateMachine::UpdateTextboxState() 
{
    auto* inputManager = InputManager::Get();

    if(inputManager->isKeyPressed(RPGMAKER::KeyCodes::CANCEL))
    {
        RenderManager::Get()->CloseTextBox();
        ChangeState(SystemStates::RUN_EMU);
    }
}

void SystemStateMachine::UpdateChoiceState() 
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
            ChangeState(SystemStates::RUN_EMU);
        }
    }
    else if (inputManager->isKeyPressed(RPGMAKER::KeyCodes::SELECT))
    {
        int choiceIndex = renderManager->CloseChoice();
        ChangeState(SystemStates::RUN_EMU);
    }
}

void SystemStateMachine::UpdateInputState() 
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
        ChangeState(SystemStates::RUN_EMU);
    }
}

}; // namespace rpgenv

