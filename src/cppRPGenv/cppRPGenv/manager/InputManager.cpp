#include "InputManager.h"

#include <cassert>

#include <SFML/Window.hpp>

#include "cppRPGenv/manager/RenderManager.h"

namespace rpgenv
{

bool InputManager::isKeyPressed(RPGMAKER::KeyCodes key)
{
    if(!RenderManager::Get()->isWindowFocused())
    {
        return false;
    }

    if(sf::Keyboard::isKeyPressed(ConvertKeyCodeToSFML(key)))
    {
        return true;
    }

    return false;
}

sf::Keyboard::Key InputManager::ConvertKeyCodeToSFML(RPGMAKER::KeyCodes key)
{
    switch(key)
    {
        case RPGMAKER::KeyCodes::DOWN:
            return sf::Keyboard::Down;
    
        case RPGMAKER::KeyCodes::LEFT:
            return sf::Keyboard::Left;

        case RPGMAKER::KeyCodes::RIGHT:
            return sf::Keyboard::Right;

        case RPGMAKER::KeyCodes::UP:
            return sf::Keyboard::Up;

        case RPGMAKER::KeyCodes::SELECT:
            return sf::Keyboard::Enter;

        case RPGMAKER::KeyCodes::CANCEL:
            return sf::Keyboard::Escape;

        case RPGMAKER::KeyCodes::SHIFT:
            return sf::Keyboard::LShift;

        case RPGMAKER::KeyCodes::NUMBER_0:
            return sf::Keyboard::Num0;

        case RPGMAKER::KeyCodes::NUMBER_1:
            return sf::Keyboard::Num1;
 
        case RPGMAKER::KeyCodes::NUMBER_2:
            return sf::Keyboard::Num2;

        case RPGMAKER::KeyCodes::NUMBER_3:
            return sf::Keyboard::Num3;

        case RPGMAKER::KeyCodes::NUMBER_4:
            return sf::Keyboard::Num4;

        case RPGMAKER::KeyCodes::NUMBER_5:
            return sf::Keyboard::Num5;

        case RPGMAKER::KeyCodes::NUMBER_6:
            return sf::Keyboard::Num6;

        case RPGMAKER::KeyCodes::NUMBER_7:
            return sf::Keyboard::Num7;

        case RPGMAKER::KeyCodes::NUMBER_8:
            return sf::Keyboard::Num8;

        case RPGMAKER::KeyCodes::NUMBER_9:
            return sf::Keyboard::Num9;

        case RPGMAKER::KeyCodes::SYMBOL_PLUS:
            return sf::Keyboard::Add;

        case RPGMAKER::KeyCodes::SYMBOL_MINUS:
            return sf::Keyboard::Subtract;

        case RPGMAKER::KeyCodes::SYMBOL_MUL:
            return sf::Keyboard::Multiply;

        case RPGMAKER::KeyCodes::SYMBOL_DIV:
            return sf::Keyboard::Divide;

        case RPGMAKER::KeyCodes::SYMBOL_DOT:
            return sf::Keyboard::Comma;
        
        default:
            return sf::Keyboard::Unknown;
    }
}

};
