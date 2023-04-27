#include <SFML/Graphics.hpp>

#include "interface/RPGMakerInterface.h"

#include "emu/EMUEntryPoint.h"

int main (int argc, char* argv[]) 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}