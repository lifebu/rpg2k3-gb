#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <core/lcf/event/EventCommandFactoryDef.h>

#include "structure/Manager.h"
// TODO: this should be forward declared. Or we use a simple interface class for the Render Manager. Users should not know these classes here.
#include "renderer/TextBox.h"
#include "renderer/ChoiceBox.h"
#include "renderer/InputBox.h"

namespace rpgenv 
{

class RenderManager : public Manager<RenderManager>
{
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr std::string_view FONT_PATH = "data/GamegirlClassic.ttf";

public:
    void Init() override;
    void Render();

    // Window
    sf::Window& GetWindow();
    bool isWindowOpen();
    bool isWindowFocused();

    // Debug Text
    void ShowDebugText(std::string text);

    // Textbox
    void OpenTextBox(std::string text);
    void CloseTextBox();

    // Choices
    void OpenChoiceBox(std::vector<std::string> choices, lcf::Choices::ChoiceCaseOnCancel cancelBehaviour);
    void MoveChoice(int delta);
    bool ClosingChoiceAllowed();
    int CancelChoice();
    // returns the index of the choice.
    int CloseChoice();

    // InputNumber
    void OpenNumberInput(uint8_t numOfDigits);
    void ChangeSelectedNumber(int delta);
    void MoveSelectedNumber(int delta);
    int CloseNumberInput();


private:
    sf::RenderWindow m_Window;

    // Text
    sf::Font m_Font;
    sf::Text m_DebugText;
    renderer::TextBox m_TextBox;

    // ChoiceBox
    renderer::ChoiceBox m_ChoiceBox;

    // InputBox
    renderer::InputBox m_InputBox;

    // Pictures are pixel in this texture.
    sf::Texture m_PictureTexture;
    sf::Sprite m_PictureSprite;
};

}