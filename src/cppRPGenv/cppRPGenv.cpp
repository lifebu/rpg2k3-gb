#include "system/SystemCore.h"

int main (int argc, char* argv[]) 
{
    rpgenv::SystemCore systemCore;
    systemCore.Init();

    while (!systemCore.ShouldShutdown())
    {
        systemCore.Update();
    }

    systemCore.Shutdown();

    return 0;
}