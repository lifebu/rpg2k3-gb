#pragma once

#include <SFML/Graphics.hpp>

namespace rpgenv 
{

class RenderManager
{
private:
    RenderManager() = default;

public:
    static RenderManager* Get();

    void Init();
    void Shutdown();

    void Render();

    sf::Window& GetWindow();
    bool isWindowOpen();

private:
    sf::RenderWindow m_Window;

    sf::Font m_TestFont;
    sf::Text m_TestText;
};

}