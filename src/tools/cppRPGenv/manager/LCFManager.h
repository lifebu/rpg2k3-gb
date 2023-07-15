#pragma once

#include <string>

#include <core/lcf/Database.h>
#include <core/lcf/Map.h>
#include <core/structure/Singleton.h>

#include "structure/ManagerInterface.h"

namespace rpgenv 
{

// Manages access and lifetime of lcf files (database, maps).
class LCFManager : public Singleton<LCFManager>, public IManager
{
private:
    enum class LoadingPhases
    {
        NOT_LOADED,
        LOADING_DATABASE,
        LOADING_MAP,
        LOADING_FINISHED
    };

public:
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