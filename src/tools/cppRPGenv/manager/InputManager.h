#pragma once

#include <SFML/Window.hpp>

#include "core/def/RPGMaker.h"

namespace rpgenv 
{

class InputManager
{
private:
    InputManager() = default;

public:
    static InputManager* Get();

    bool isKeyPressed(RPGMAKER::KeyCodes key);

    void Init();
    void Shutdown();

private:
    sf::Keyboard::Key ConvertKeyCodeToSFML(RPGMAKER::KeyCodes key);
};

}