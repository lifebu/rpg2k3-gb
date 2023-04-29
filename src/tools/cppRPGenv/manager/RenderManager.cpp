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
    m_Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "C++ RPG Env", sf::Style::Titlebar | sf::Style::Close);
    m_Window.setFramerateLimit(60);
    m_Window.setPosition(sf::Vector2i(1920 / 2 - WINDOW_WIDTH / 2, 1080 / 2 - WINDOW_HEIGHT / 2));

    // TODO: Just some test stuff for now!
    if(!m_TestFont.loadFromFile("data/GamegirlClassic.ttf"))
    {
        std::cout << "could not load the font!" << std::endl;
        return;
    }

    m_TestText.setFont(m_TestFont);
    m_TestText.setCharacterSize(24);
    m_TestText.setFillColor(sf::Color::White);
}

void RenderManager::Shutdown() 
{
    
}

void RenderManager::Render()
{
    m_TestText.setPosition( m_Window.getView().getCenter());

    m_Window.clear(sf::Color::Black);

    m_Window.draw(m_TestText);

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

void RenderManager::ShowText(std::string text) 
{
    m_TestText.setString(text);
    sf::FloatRect textRect = m_TestText.getLocalBounds();
    m_TestText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
}

};
