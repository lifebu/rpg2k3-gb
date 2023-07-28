#pragma once

namespace sf
{
    class Clock;
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
    void Render(sf::RenderWindow& window, sf::Clock& clock);

private:
    void BuildImGUI();
};

}