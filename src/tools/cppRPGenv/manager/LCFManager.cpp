#include "LCFManager.h"

#include <iostream>

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

void LCFManager::LoadLCFFiles()
{
    
}

};
