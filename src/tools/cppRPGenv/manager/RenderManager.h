#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "render_manager/TextBox.h"

namespace rpgenv 
{

class RenderManager
{
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr std::string_view FONT_PATH = "data/GamegirlClassic.ttf";

private:
    RenderManager() = default;

public:
    static RenderManager* Get();

    void Init();
    void Shutdown();
    void Render();

    sf::Window& GetWindow();
    bool isWindowOpen();
    bool isWindowFocused();

    void ShowDebugText(std::string text);

    void OpenTextBox(std::string text);
    void CloseTextBox();

private:
    sf::RenderWindow m_Window;

    // Text
    sf::Font m_Font;
    sf::Text m_DebugText;
    renderer::TextBox m_TextBox;
};

}