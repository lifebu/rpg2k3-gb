#pragma once

#include <SFML/Window.hpp>

#include "core/def/RPGMaker.h"
#include "structure/Manager.h"

namespace rpgenv 
{

class InputManager : public Manager<InputManager>
{
public:
    bool isKeyPressed(RPGMAKER::KeyCodes key);

private:
    sf::Keyboard::Key ConvertKeyCodeToSFML(RPGMAKER::KeyCodes key);
};

}