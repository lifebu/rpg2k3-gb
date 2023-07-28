#include "LCFManager.h"

#include <cassert>
#include <iostream>
#include <filesystem>

#include <core/def/Globals.h>
#include <core/lcf_serializers/DatabaseSerializer.h>
#include <core/lcf_serializers/MapSerializer.h>
#include <core/lcf_serializers/MapSerializerRAPID.h>
#include <core/structure/Logger.h>
#include <core/utilities/RPGHelper.h>

namespace fs = std::filesystem;

const static std::string ERR_NO_PROJECT_FILE = "Could not find Projectfile. Did you generate a project using gb2rpg? Missing: ";

namespace rpgenv
{

void LCFManager::ContinueLoading()
{
    assert(m_LoadingPhases != LoadingPhases::LOADING_FINISHED);

    switch(m_LoadingPhases)
    {
        case LoadingPhases::NOT_LOADED:
        {
            m_LoadingPhases = LoadingPhases::LOADING_DATABASE;
        } break;
        case LoadingPhases::LOADING_DATABASE:
        {
            std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::DATABASE_FILE;
            if(!fs::exists({filePath})) 
            {
                Logger::Get()->Log(ERR_NO_PROJECT_FILE + filePath, LogLevel::ERROR);
                m_HadLoadingError = true;
            }
            else 
            {
                m_Database = lcf::DatabaseSerializer::FromFile(filePath);
            }

            m_LoadingPhases = LoadingPhases::LOADING_MAP;
        } break;
        case LoadingPhases::LOADING_MAP:
        {
            std::string fileName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(1) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
            std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + fileName;
            if(!fs::exists({filePath})) 
            {
                Logger::Get()->Log(ERR_NO_PROJECT_FILE + filePath, LogLevel::ERROR);
                m_HadLoadingError = true;
            }
            else 
            {
                m_Map = lcf::MapSerializer::FromFile(filePath);
            }

            m_LoadingPhases =  m_HadLoadingError ? LoadingPhases::LOADING_ERROR : LoadingPhases::LOADING_FINISHED;
        } break;
    }
}

bool LCFManager::IsLoadingFinished() 
{ 
    return m_LoadingPhases == LoadingPhases::LOADING_FINISHED; 
}

bool LCFManager::HadLoadingErrors() 
{ 
    return m_LoadingPhases == LoadingPhases::LOADING_ERROR; 
}

lcf::Database &LCFManager::GetDatabase() 
{
    return m_Database;
}

lcf::Map &LCFManager::GetMap()
{
    return m_Map;
}

}; // namespace rpgenv
