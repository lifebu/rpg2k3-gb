#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <core/lcf/event/EventCommandFactoryDef.h>
#include <core/structure/ManagerInterface.h>
#include <core/structure/Singleton.h>

// TODO: this should be forward declared. Or we use a simple interface class for the Render Manager. Users should not know these classes here.
#include "cppRPGenv/manager/renderer/TextBox.h"
#include "cppRPGenv/manager/renderer/ChoiceBox.h"
#include "cppRPGenv/manager/renderer/InputBox.h"
#include "cppRPGenv/manager/renderer/RenderDef.h"
#include "cppRPGenv/manager/renderer/ImGUIRenderer.h"

namespace rpgenv 
{

class RenderManager : public Singleton<RenderManager>, public IManager
{
private:
    static constexpr std::string_view FONT_PATH = "data/GamegirlClassic.ttf";
    static constexpr std::string_view STATIC_IMAGE_PATH = "data/background.png";

public:
    void Init() override;
    void Shutdown() override;

    void PollEvents();
    void Render();

    // Window
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

    // Pictures
    void PutPixel(int x, int y, sf::Color color);

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
    sf::Image m_PictureCPUTexture; // PutPixel changes the CPU texture
    sf::Texture m_PictureGPUTexture; // This is swapped with the CPU texture once per frame.
    sf::Sprite m_PictureSprite;

    // ImGUI
    ImGUIRenderer m_ImGUIRenderer;
    sf::Clock m_RenderClock;
    sf::Time m_LastDelta;
};

}