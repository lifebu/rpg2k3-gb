#pragma once

namespace rpgenv 
{

// Manages access and lifetime of lcf files (database, maps).
class LCFManager
{
private:
    LCFManager() = default;

public:
    static LCFManager* Get();

    void Init();
    void Shutdown();

    void LoadLCFFiles();
};

}