#include <core/structure/Logger.h>

#include "manager/InputManager.h"
#include "manager/LCFManager.h"
#include "manager/RenderManager.h"
#include "manager/VariableManager.h"
#include "system/SystemStateMachine.h"
#include "interface_impl/RPGMakerImpl.h"


int main (int argc, char* argv[]) 
{
    core::Logger                logger;
    rpgenv::InputManager        inputManager;
    rpgenv::LCFManager          lcfManager;
    rpgenv::RenderManager       renderManager; 
    rpgenv::VariableManager     variableManager;
    rpgenv::RPGMakerImpl        rpgMakerInterface;
    rpgenv::SystemStateMachine  systemStateMachine;

    logger.Init("cppRPGenv_", core::LOGMASK::LOG_MODE_FILE | core::LOGMASK::LOG_MODE_STDOUT);
    inputManager.Init();
    lcfManager.Init();
    renderManager.Init();
    variableManager.Init();
    systemStateMachine.Init(rpgenv::SystemStates::LOADING);

    while (renderManager.isWindowOpen())
    {
        renderManager.PollEvents();
        systemStateMachine.Update();
        renderManager.Render();
    }

    logger.Shutdown();
    inputManager.Shutdown();
    lcfManager.Shutdown();
    renderManager.Shutdown();
    variableManager.Shutdown();

    return 0;
}