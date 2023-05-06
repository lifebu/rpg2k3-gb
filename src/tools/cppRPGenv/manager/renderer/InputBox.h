#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace rpgenv 
{

namespace renderer
{

class InputBox final : public sf::Drawable
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

}