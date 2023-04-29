#include "RenderManager.h"

#include <iostream>

namespace rpgenv
{

static RenderManager* m_Instance = nullptr;

RenderManager* RenderManager::Get() 
{
    if(!m_Instance)
    {
        m_Instance = new RenderManager();
    }
    return m_Instance; 
}

void RenderManager::Init() 
{
    m_Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "C++ RPG Env", 
        sf::Style::Titlebar | sf::Style::Close);

    // Position window in the middle of the screen.
    auto currentRes = sf::VideoMode::getDesktopMode();
    m_Window.setPosition(sf::Vector2i(
        currentRes.width / 2 - WINDOW_WIDTH / 2, 
        currentRes.height / 2 - WINDOW_HEIGHT / 2));
    
    m_Window.setFramerateLimit(60);
    
    if(!m_Font.loadFromFile(std::string(FONT_PATH)))
    {
        std::cout << "Could not load the font: " << FONT_PATH << std::endl;
        return;
    }

    m_DebugText.setFont(m_Font);
    m_DebugText.setCharacterSize(24);
    m_DebugText.setFillColor(sf::Color::White);

    // Initialize Textbox
    m_TextBox.SetFont(m_Font);
}

void RenderManager::Shutdown() 
{
    
}

void RenderManager::Render()
{
    m_Window.clear(sf::Color(128, 0, 128));

    // DebugText
    {
        m_Window.draw(m_DebugText);
    }

    if(m_TextBox.m_IsOpen)
    {
        m_Window.draw(m_TextBox);
    }

    m_Window.display();
}

sf::Window& RenderManager::GetWindow()
{
    return m_Window;
}

bool RenderManager::isWindowOpen()
{
    return m_Window.isOpen();
}

void RenderManager::ShowDebugText(std::string text) 
{
    m_DebugText.setString(text);

    // Center the debug text
    sf::FloatRect textRect = m_DebugText.getLocalBounds();
    m_DebugText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    m_DebugText.setPosition(m_Window.getView().getCenter());
}

void RenderManager::OpenTextBox(std::string text)
{
    const sf::View& view = m_Window.getView();

    m_TextBox.m_IsOpen = true;
    m_TextBox.SetupTextbox(view, text);
}

void RenderManager::CloseTextBox()
{
    m_TextBox.m_IsOpen = false;
}

};
