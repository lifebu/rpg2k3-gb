#include "system/SystemCore.h"

#include <memory>

int main (int argc, char* argv[]) 
{
    auto systemCore = std::make_unique<rpgenv::SystemCore>();
    systemCore->Init();

    while (!systemCore->ShouldShutdown())
    {
        systemCore->Update();
    }

    systemCore->Shutdown();

    return 0;
}