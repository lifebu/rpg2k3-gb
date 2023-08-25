#include "ChoiceBox.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>

#include <core/structure/Logger.h>

namespace rpgenv
{

namespace renderer
{

ChoiceBox::ChoiceBox()
{
    m_Text.setLineSpacing(1.5f);
    m_Text.setCharacterSize(17);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setOutlineColor(sf::Color::Black);
    m_Text.setOutlineThickness(2.0f);

    m_Box.setFillColor(sf::Color(0, 0, 128, 230));

    m_SelectionBox.setOutlineColor(sf::Color::White);
    m_SelectionBox.setOutlineThickness(1.0f);
    m_SelectionBox.setFillColor(sf::Color::Transparent);
}

void ChoiceBox::SetFont(sf::Font &font)
{
    m_Text.setFont(font);
}

void ChoiceBox::Setup(const sf::View& view, std::vector<std::string> choices, 
    lcf::Choices::ChoiceCaseOnCancel cancelBehaviour)
{
    m_CancelBehaviour = cancelBehaviour;
    m_SelectedIndex = 0;

    // Setup the Text:
    m_Text.setString(generateChoiceString(choices));

    // Configure the box:
    m_Box.setPosition(sf::Vector2f(0.0f, view.getSize().y * (1.0 - CHOICE_BOX_SIZE)));
    m_Box.setSize(sf::Vector2f(view.getSize().x, view.getSize().y * CHOICE_BOX_SIZE));

    // Position text in box
    sf::Vector2f textPos = m_Box.getPosition();
    textPos.x = m_Box.getPosition().x + (m_Box.getSize().x - m_Text.getLocalBounds().width) / 2.0f;
    textPos.x = m_Box.getPosition().x + CHOICE_TEXT_LEFT_MARGIN * m_Box.getSize().x;
    textPos.y = m_Box.getPosition().y + (m_Box.getSize().y - m_Text.getLocalBounds().height) / 2.0f;

    m_Text.setPosition(textPos);

    // Position the SelectionBox:
    calcSelectionBoxPos();
}

void ChoiceBox::MoveChoice(int delta)
{
    m_SelectedIndex += delta;
    m_SelectedIndex = (m_SelectedIndex >= 0) 
        ? (m_SelectedIndex % MAX_NUM_CHOICES) 
        : (m_SelectedIndex + MAX_NUM_CHOICES);
    
    calcSelectionBoxPos();
}

lcf::Choices::ChoiceCaseOnCancel ChoiceBox::GetCancelBehaviour()
{
    return m_CancelBehaviour;
}

int ChoiceBox::GetChoiceIndex()
{
    return m_SelectedIndex;
}

void ChoiceBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_Box);
    target.draw(m_SelectionBox);
    target.draw(m_Text);
}

void ChoiceBox::calcSelectionBoxPos()
{
    sf::Vector2f textPos = m_Text.getGlobalBounds().getPosition();
    sf::Vector2f textSize = m_Text.getGlobalBounds().getSize();

    // Calculate the position based on the current selection.
    float offset = textSize.y / static_cast<float>(MAX_NUM_CHOICES);
    float selectionPosYOffset = offset * static_cast<float>(m_SelectedIndex);

    sf::Vector2f selectionPos = textPos + sf::Vector2f(0.0f, selectionPosYOffset);
    sf::Vector2f selectionSize = sf::Vector2f(textSize.x, offset);

    // Apply a small margin
    selectionPos -= sf::Vector2f(SELECTION_BOX_MARGIN, SELECTION_BOX_MARGIN);
    selectionSize += sf::Vector2f(2.0f * SELECTION_BOX_MARGIN, 2.0f * SELECTION_BOX_MARGIN);

    m_SelectionBox.setPosition(selectionPos);
    m_SelectionBox.setSize(selectionSize);
}

std::string ChoiceBox::generateChoiceString(std::vector<std::string>& choices)
{
    std::string newText;
    for(auto choiceIt = choices.begin(); choiceIt < choices.end(); ++choiceIt)
    {
        const auto& choice = *choiceIt;
        if(choice.length() > MAX_CHAR_PER_LINE)
        {
            std::stringstream message;
            message << "Maximum size of a choice for the ChoiceBox is " << MAX_CHAR_PER_LINE << " characters, tried to set a choice with the size of " + choice.length() << "." << std::endl;
            core::Logger::Get()->Log(message.str(), core::LogLevel::WARNING);

            return "";
        }

        newText.append(choice);
        if(choiceIt < (choices.end() - 1))
        {
            newText.append("\n");
        }
    }

    return newText;
}

};

};