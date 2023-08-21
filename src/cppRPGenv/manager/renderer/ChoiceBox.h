#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <core/lcf/event/EventCommandFactoryDef.h>

namespace sf
{
    class View;
}

namespace rpgenv 
{

namespace renderer
{

class ChoiceBox final : public sf::Drawable
{
    static constexpr float CHOICE_BOX_SIZE = 0.25f;
    static constexpr int MAX_NUM_CHOICES = 4;
    static constexpr int MAX_CHAR_PER_LINE = 33;
    static constexpr float CHOICE_TEXT_LEFT_MARGIN = 0.025f;
    static constexpr float SELECTION_BOX_MARGIN = 2.0f;

public:
    ChoiceBox();

    void SetFont(sf::Font& font);

    void Setup(const sf::View& view, std::vector<std::string> choices,
    lcf::Choices::ChoiceCaseOnCancel cancelBehaviour);

    void MoveChoice(int delta);

    lcf::Choices::ChoiceCaseOnCancel GetCancelBehaviour();
    int GetChoiceIndex();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void calcSelectionBoxPos();
    std::string generateChoiceString(std::vector<std::string>& choices);

public:
    bool m_IsOpen = false;

private:
    sf::Text m_Text;
    sf::RectangleShape m_Box;
    sf::RectangleShape m_SelectionBox;
    lcf::Choices::ChoiceCaseOnCancel m_CancelBehaviour;
    int m_SelectedIndex = 0;
};

}

}