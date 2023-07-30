#pragma once

#include "manager/renderer/RenderDef.h"

namespace sf
{
    class Time;
    class Event;
    class RenderWindow;
};

namespace rpgenv 
{

class ImGUIRenderer
{
public:
    void Init(sf::RenderWindow& window);
    void Shutdown();

    void ProcessEvent(const sf::Event& event);
    void Render(sf::RenderWindow& window, const sf::Time& deltaTime);

private:
    void BuildImGUI(const sf::Time& deltaTime);

private:
    bool m_LogIsEnabled = false;
    float m_ExpandedSize = (1.0f - RENDERER::TEXT_BOX_SIZE) * RENDERER::WINDOW_HEIGHT;
};

}