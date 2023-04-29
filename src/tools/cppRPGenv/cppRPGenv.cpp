#include <SFML/Graphics.hpp>

#include <emu/EMUEntryPoint.h>

#include "interface_impl/RPGMakerImpl.h"


int main (int argc, char* argv[]) 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    emu::EMUEntryPoint emulator;
    rpgenv::RPGMakerImpl rpgMakerInterface;

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

        emulator.RPGMain(&rpgMakerInterface);

        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}