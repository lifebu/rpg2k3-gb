#include "InputManager.h"

#include <iostream>

namespace rpgenv
{

static InputManager* m_Instance = nullptr;

InputManager* InputManager::Get() 
{
    if(!m_Instance)
    {
        m_Instance = new InputManager();
    }
    return m_Instance; 
}

void InputManager::Init() 
{

}

void InputManager::Shutdown() 
{

}

};
