#pragma once

#include <string>

#include <SFML/Graphics.hpp>

namespace rpgenv 
{

class RenderManager
{
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;

private:
    RenderManager() = default;

public:
    static RenderManager* Get();

    void Init();
    void Shutdown();

    void Render();

    sf::Window& GetWindow();
    bool isWindowOpen();

    void ShowText(std::string text);

private:
    sf::RenderWindow m_Window;

    sf::Font m_TestFont;
    sf::Text m_TestText;
};

}