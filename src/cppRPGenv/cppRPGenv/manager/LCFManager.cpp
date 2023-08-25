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
            if(!m_LoadingFuture.valid())
            {
                std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::DATABASE_FILE;
                if(!fs::exists({filePath})) 
                {
                    core::Logger::Get()->Log(ERR_NO_PROJECT_FILE + filePath, core::LogLevel::ERROR);
                    m_HadLoadingError = true;
                    m_LoadingPhases = LoadingPhases::LOADING_MAP;
                }
                else 
                {
                    m_LoadingFuture = std::async(std::launch::async, [this, filePath]()
                    {
                        // TODO: Nobody will know if this throws an exception.
                        // TODO: The Return value is not thread safe.
                        m_Database = lcf::DatabaseSerializer::FromFile(filePath);
                    });
                }
            }
            else
            {
                std::future_status result = m_LoadingFuture.wait_for(std::chrono::milliseconds(10));
                if(result == std::future_status::ready)
                {
                    m_LoadingFuture = std::future<void>();
                    m_LoadingPhases = LoadingPhases::LOADING_MAP;
                }
            }
        } break;
        case LoadingPhases::LOADING_MAP:
        {
            if(!m_LoadingFuture.valid())
            {
                std::string fileName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(1) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
                std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + fileName;
                if(!fs::exists({filePath})) 
                {
                    core::Logger::Get()->Log(ERR_NO_PROJECT_FILE + filePath, core::LogLevel::ERROR);
                    m_HadLoadingError = true;
                    m_LoadingPhases = LoadingPhases::LOADING_ERROR;
                }
                else 
                {
                    m_LoadingFuture = std::async(std::launch::async, [this, filePath]()
                    {
                        // TODO: Nobody will know if this throws an exception.
                        // TODO: The Return value is not thread safe.
                        m_Map = lcf::MapSerializer::FromFile(filePath);
                    });
                }
            }
            else
            {
                std::future_status result = m_LoadingFuture.wait_for(std::chrono::milliseconds(10));
                
                if(result == std::future_status::ready)
                {
                    m_LoadingFuture = std::future<void>();
                    m_LoadingPhases =  m_HadLoadingError ? LoadingPhases::LOADING_ERROR : LoadingPhases::LOADING_FINISHED;
                }
            }
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
