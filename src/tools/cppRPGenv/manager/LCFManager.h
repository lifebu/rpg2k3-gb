#pragma once

#include <string>

#include <core/lcf/Database.h>
#include <core/lcf/Map.h>

namespace rpgenv 
{

// Manages access and lifetime of lcf files (database, maps).
class LCFManager
{
private:
    enum class LoadingPhases
    {
        NOT_LOADED,
        LOADING_DATABASE,
        LOADING_MAP,
        LOADING_FINISHED
    };

    LCFManager() = default;

public:
    static LCFManager* Get();

    void Init();
    void Shutdown();

    void ContinueLoading();

    bool isLoadingFinished();

    lcf::Database& GetDatabase();
    lcf::Map& GetMap();

private:
    LoadingPhases m_LoadingPhases = LoadingPhases::NOT_LOADED;

    lcf::Database m_Database;
    lcf::Map m_Map;
};

}