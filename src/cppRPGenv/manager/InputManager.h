#pragma once

#include <SFML/Window.hpp>

#include <core/def/RPGMaker.h>
#include <core/structure/Singleton.h>

#include "structure/ManagerInterface.h"

namespace rpgenv 
{

// Allows easy access to inputs
class InputManager : public Singleton<InputManager>, public IManager
{
public:
    bool isKeyPressed(RPGMAKER::KeyCodes key);

private:
    sf::Keyboard::Key ConvertKeyCodeToSFML(RPGMAKER::KeyCodes key);
};

}