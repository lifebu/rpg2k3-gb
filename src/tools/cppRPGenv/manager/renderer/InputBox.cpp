#include "InputBox.h"

#include <cmath>
#include <numeric>
#include <iostream>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

namespace rpgenv
{

namespace renderer
{

InputBox::InputBox()
{
    m_Text.setLineSpacing(1.5f);
    m_Text.setCharacterSize(17);
    m_Text.setFillColor(sf::Color::White);

    m_Box.setFillColor(sf::Color(0, 0, 128));

    m_SelectionBox.setOutlineColor(sf::Color::White);
    m_SelectionBox.setOutlineThickness(1.0f);
    m_SelectionBox.setFillColor(sf::Color::Transparent);
}

void InputBox::setFont(sf::Font &font)
{
    m_Text.setFont(font);
}

void InputBox::Setup(const sf::View &view, uint8_t numOfDigits)
{
    m_Digits.clear();
    m_Digits.insert(m_Digits.end(), numOfDigits, 0);
    m_SelectionIndex = 0;

    // Setup the Text:
    m_Text.setString(generateDigitString());

    // Configure the box:
    m_Box.setPosition(sf::Vector2f(0.0f, view.getSize().y * (1.0 - CHOICE_BOX_SIZE)));
    m_Box.setSize(sf::Vector2f(view.getSize().x, view.getSize().y * CHOICE_BOX_SIZE));

    // Position text in box
    sf::Vector2f textPos = m_Box.getPosition();
    textPos.x = m_Box.getPosition().x + (m_Box.getSize().x - m_Text.getLocalBounds().width) / 2.0f;
    textPos.x = m_Box.getPosition().x + TEXT_LEFT_MARGIN * m_Box.getSize().x;
    textPos.y = m_Box.getPosition().y + TEXT_TOP_MARGIN * m_Box.getSize().y;

    m_Text.setPosition(textPos);

    calcSelectionBoxPos();
}

void InputBox::IncreaseDigit(int delta)
{
    auto& digit = m_Digits.at(m_SelectionIndex);

    digit += delta;
    digit = (digit >= 0) 
        ? (digit % MAX_VALUE_DIGIT) 
        : (digit + MAX_VALUE_DIGIT);
    
    m_Text.setString(generateDigitString());
}

void InputBox::MoveDigit(int delta)
{
    m_SelectionIndex += delta;
    m_SelectionIndex = (m_SelectionIndex >= 0) 
        ? (m_SelectionIndex % m_Digits.size()) 
        : (m_SelectionIndex + m_Digits.size());
    
    calcSelectionBoxPos();
}

int InputBox::GetNumber()
{
    int sum = 0;

    for(int i = 0; i < m_Digits.size(); ++i)
    {
        int digit = m_Digits.at(i);
        sum += digit * std::pow(10, (m_Digits.size() - (i + 1)));
    }

    return sum;
}

void InputBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_Box);
    target.draw(m_SelectionBox);
    target.draw(m_Text);
}

void InputBox::calcSelectionBoxPos()
{
    sf::Vector2f textPos = m_Text.getGlobalBounds().getPosition();
    sf::Vector2f textSize = m_Text.getGlobalBounds().getSize();

    // Calculate the position based on the current selection.
    float offset = textSize.x / static_cast<float>(m_Digits.size() * 2 - 1);
    float selectionPosXOffset = offset * static_cast<float>(m_SelectionIndex * 2);

    sf::Vector2f selectionPos = textPos + sf::Vector2f(selectionPosXOffset, 0.0f);
    sf::Vector2f selectionSize = sf::Vector2f(offset, textSize.y);

    // Apply a small margin
    //selectionPos -= sf::Vector2f(SELECTION_BOX_MARGIN, SELECTION_BOX_MARGIN);
    //selectionSize += sf::Vector2f(2.0f * SELECTION_BOX_MARGIN, 2.0f * SELECTION_BOX_MARGIN);

    m_SelectionBox.setPosition(selectionPos);
    m_SelectionBox.setSize(selectionSize);
}

std::string InputBox::generateDigitString()
{
    std::string digitString;
    for(auto digitIt = m_Digits.begin(); digitIt < m_Digits.end(); ++digitIt)
    {
        digitString += std::to_string(*digitIt) + " ";
    }

    digitString.pop_back();

    return digitString;
}

}
}