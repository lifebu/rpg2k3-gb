#include "TextBox.h"

#include <iostream>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

namespace rpgenv
{

namespace renderer
{

TextBox::TextBox()
{
    m_Text.setLineSpacing(1.5f);
    m_Text.setCharacterSize(12);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setOutlineColor(sf::Color::Black);
    m_Text.setOutlineThickness(2.0f);

    m_Box.setFillColor(sf::Color(0, 0, 128, 230));
}

void TextBox::SetFont(sf::Font& font)
{
    m_Text.setFont(font);
}

void TextBox::Setup(const sf::View& view, std::string text)
{
    int size = text.size();
    if(size > MAX_STRING_SIZE)
    {
        std::cout << "Maximum size of text for the Textbox is " << MAX_STRING_SIZE << " characters, tried to set a text with the size of " + text.size() << "." << std::endl;
        return;
    }

    ApplyWordWrap(text);

    // Configure the box:
    m_Box.setPosition(sf::Vector2f(0.0f, view.getSize().y * (1.0 - TEXT_BOX_SIZE)));
    m_Box.setSize(sf::Vector2f(view.getSize().x, view.getSize().y * TEXT_BOX_SIZE));

    // Configure the text:
    m_Text.setString(text);
    
    // Position text in box
    sf::Vector2f textPos = m_Box.getPosition();
    textPos.x = m_Box.getPosition().x + (m_Box.getSize().x - m_Text.getLocalBounds().width) / 2.0f;
    textPos.y = m_Box.getPosition().y + (m_Box.getSize().y - m_Text.getLocalBounds().height) / 2.0f;

    m_Text.setPosition(textPos);
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_Box);
    target.draw(m_Text);    
}

void TextBox::ApplyWordWrap(std::string& text)
{
    int currCharsInLine = 0;

    for(std::size_t i = 0; i < text.size(); ++i)
    {
        char c = text[i];

        if(currCharsInLine >= MAX_CHAR_PER_LINE)
        {
            text.insert(i - 1, "\n");
            currCharsInLine = 0;
        }

        if(c == '\n')
        {
            currCharsInLine = 0;
        }
        else
        {
            currCharsInLine++;
        }
    }
}

};

};