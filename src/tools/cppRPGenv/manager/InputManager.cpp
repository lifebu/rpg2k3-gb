#include "InputManager.h"

#include <SFML/Window.hpp>

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

bool InputManager::isKeyPressed(RPGMAKER::KeyCodes key)
{
    switch(key)
    {
        case RPGMAKER::KeyCodes::DOWN:
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                return true;
            }
        }
        case RPGMAKER::KeyCodes::LEFT:
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                return true;
            }
        }
        case RPGMAKER::KeyCodes::RIGHT:
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                return true;
            }
        }
        case RPGMAKER::KeyCodes::UP:
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                return true;
            }
        }
    }

    return false;
}

void InputManager::Init() 
{

}

void InputManager::Shutdown() 
{

}

};
