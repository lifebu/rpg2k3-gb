#include "LCFManager.h"

#include <cassert>
#include <iostream>

#include <core/def/Globals.h>
#include <core/lcf_serializers/DatabaseSerializer.h>
#include <core/lcf_serializers/MapSerializer.h>
#include <core/lcf_serializers/MapSerializerRAPID.h>
#include <core/utilities/RPGHelper.h>

namespace rpgenv
{

static LCFManager* m_Instance = nullptr;

LCFManager* LCFManager::Get() 
{
    if(!m_Instance)
    {
        m_Instance = new LCFManager();
    }
    return m_Instance; 
}

void LCFManager::Init() 
{

}

void LCFManager::Shutdown() 
{

}

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
            //m_Database = lcf::DatabaseSerializer::FromFile(GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::DATABASE_FILE);
            m_LoadingPhases = LoadingPhases::LOADING_MAP;
        }break;
        case LoadingPhases::LOADING_MAP:
        {
            std::string fileName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(1) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
            std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + fileName;
            //m_Map = lcf::MapSerializer::FromFile(filePath);
            m_LoadingPhases = LoadingPhases::LOADING_FINISHED;
        }break;
    }
}

bool LCFManager::isLoadingFinished() 
{ 
    return m_LoadingPhases == LoadingPhases::LOADING_FINISHED; 
}
}; // namespace rpgenv
