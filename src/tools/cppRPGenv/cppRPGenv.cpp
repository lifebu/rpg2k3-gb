#include "system/SystemCore.h"

int main (int argc, char* argv[]) 
{
    auto* systemCore = rpgenv::SystemCore::Get();
    systemCore->Init();

    while (!systemCore->ShouldShutdown())
    {
        systemCore->Update();
    }

    systemCore->Shutdown();

    return 0;
}