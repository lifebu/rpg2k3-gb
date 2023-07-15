#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <cstdint>

namespace sf
{
    class View;
    class Font;
}

namespace rpgenv 
{

namespace renderer
{

class InputBox final : public sf::Drawable
{
    static constexpr float CHOICE_BOX_SIZE = 0.25f;
    static constexpr int MAX_NUM_DIGITS = 7;
    static constexpr int MAX_VALUE_DIGIT = 9;
    static constexpr float TEXT_LEFT_MARGIN = 0.025f;
    static constexpr float TEXT_TOP_MARGIN = 0.100f;
    static constexpr float SELECTION_BOX_MARGIN = 2.0f;

public:
    InputBox();

    void SetFont(sf::Font& font);

    void Setup(const sf::View& view, uint8_t numOfDigits);

    void IncreaseDigit(int delta);
    void MoveDigit(int delta);
    int GetNumber();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void calcSelectionBoxPos();
    std::string generateDigitString();

public:
    bool m_IsOpen = false;

private:
    sf::Text m_Text;
    sf::RectangleShape m_Box;
    sf::RectangleShape m_SelectionBox;
    std::vector<uint8_t> m_Digits;
    int m_SelectionIndex = 0;
};

}

}