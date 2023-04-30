#pragma once

#include <string>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
    class View;
}

namespace rpgenv 
{

namespace renderer
{

class TextBox final : public sf::Drawable
{
    static constexpr float TEXT_BOX_SIZE = 0.25f;
    static constexpr int MAX_STRING_SIZE = 200;
    static constexpr int MAX_CHAR_PER_LINE = 50;

public:
    TextBox();

    void SetFont(sf::Font& font);

    void SetupTextbox(const sf::View& view, std::string text);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void ApplyWordWrap(std::string& text);

public:
    bool m_IsOpen = false;

private:
    float m_HeightPercent = 0.35f;
    sf::Text m_Text;
    sf::RectangleShape m_Box;

};

}

}