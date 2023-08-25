#include "RenderManager.h"

#include "core/structure/Logger.h"

#include <cassert>
#include <iostream>

namespace rpgenv
{

void RenderManager::Init() 
{
    m_Window.create(sf::VideoMode(RENDERER::WINDOW_WIDTH, RENDERER::WINDOW_HEIGHT), "C++ RPG Env", 
        sf::Style::Titlebar | sf::Style::Close);

    // Position window in the middle of the screen.
    auto currentRes = sf::VideoMode::getDesktopMode();
    m_Window.setPosition(sf::Vector2i(
        currentRes.width / 2 - RENDERER::WINDOW_WIDTH / 2, 
        currentRes.height / 2 - RENDERER::WINDOW_HEIGHT / 2));
    
    m_Window.setFramerateLimit(60);
    
    if(!m_Font.loadFromFile(std::string(FONT_PATH)))
    {
        core::Logger::Get()->Log("Could not load the font: " + std::string(FONT_PATH), core::LogLevel::ERROR);
        return;
    }

    m_DebugText.setFont(m_Font);
    m_DebugText.setCharacterSize(24);
    m_DebugText.setFillColor(sf::Color::White);
    m_DebugText.setOutlineColor(sf::Color::Black);
    m_DebugText.setOutlineThickness(3.0f);

    // Initialize Textbox
    m_TextBox.SetFont(m_Font);

    // Initialize ChoiceBox
    m_ChoiceBox.SetFont(m_Font);

    // Initialize InputBox
    m_InputBox.SetFont(m_Font);

    // Pictures
    if(!m_PictureGPUTexture.loadFromFile(std::string(STATIC_IMAGE_PATH)))
    {
        core::Logger::Get()->Log("Could not load the texture: " + std::string(STATIC_IMAGE_PATH), core::LogLevel::ERROR);
        return;
    }
    m_PictureGPUTexture.setSmooth(false);
    m_PictureSprite.setTexture(m_PictureGPUTexture);

    if(!m_PictureCPUTexture.loadFromFile(std::string(STATIC_IMAGE_PATH)))
    {
        core::Logger::Get()->Log("Could not load the texture: " + std::string(STATIC_IMAGE_PATH), core::LogLevel::ERROR);
        return;
    }

    // Set correct scale.
    auto localBounds = m_PictureSprite.getLocalBounds();
    float xScale = m_Window.getSize().x / localBounds.width;
    float yScale = (m_Window.getSize().y - RENDERER::MENU_HEIGHT) / localBounds.height;
    float minScale = std::min(xScale, yScale);
    m_PictureSprite.setScale(minScale, minScale);

    // Center the picture.
    auto globalBounds = m_PictureSprite.getGlobalBounds();
    float missingX = m_Window.getSize().x - globalBounds.width;
    m_PictureSprite.setPosition(missingX / 2.0f, RENDERER::MENU_HEIGHT);

    // Initialize ImGUI
    m_ImGUIRenderer.Init(m_Window);
}

void RenderManager::Shutdown() 
{
    m_ImGUIRenderer.Shutdown();
}

void RenderManager::PollEvents() 
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        m_ImGUIRenderer.ProcessEvent(event);

        if(event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
    }
}

void RenderManager::Render() 
{
    m_LastDelta = m_RenderClock.restart();
    m_Window.clear(sf::Color::Black);

    // Pictures
    {
        // CPU to GPU texture swap.
        m_PictureGPUTexture.loadFromImage(m_PictureCPUTexture);
        m_Window.draw(m_PictureSprite);
    }

    // DebugText
    {
        m_Window.draw(m_DebugText);
    }

    if(m_TextBox.m_IsOpen)
    {
        m_Window.draw(m_TextBox);
    }

    if(m_ChoiceBox.m_IsOpen)
    {
        m_Window.draw(m_ChoiceBox);
    }

    if(m_InputBox.m_IsOpen)
    {
        m_Window.draw(m_InputBox);
    }

    m_ImGUIRenderer.Render(m_Window, m_LastDelta);

    m_Window.display();
}

// Window
bool RenderManager::isWindowOpen()
{
    return m_Window.isOpen();
}

bool RenderManager::isWindowFocused()
{
    return m_Window.hasFocus();
}

// Debug Text
void RenderManager::ShowDebugText(std::string text) 
{
    m_DebugText.setString(text);

    // Center the debug text
    sf::FloatRect textRect = m_DebugText.getLocalBounds();
    m_DebugText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    m_DebugText.setPosition(m_Window.getView().getCenter());
}

// Textbox
void RenderManager::OpenTextBox(std::string text)
{
    const sf::View& view = m_Window.getView();

    m_TextBox.m_IsOpen = true;
    m_TextBox.Setup(view, text);
}

void RenderManager::CloseTextBox()
{
    m_TextBox.m_IsOpen = false;
}

// Choices
void RenderManager::OpenChoiceBox(std::vector<std::string> choices,
    lcf::Choices::ChoiceCaseOnCancel cancelBehaviour) 
{
    const sf::View& view = m_Window.getView();

    m_ChoiceBox.m_IsOpen = true;
    m_ChoiceBox.Setup(view, choices, cancelBehaviour);
}

void RenderManager::MoveChoice(int delta) 
{
    m_ChoiceBox.MoveChoice(delta);
}

bool RenderManager::ClosingChoiceAllowed()
{
    return m_ChoiceBox.GetCancelBehaviour() != lcf::Choices::ChoiceCaseOnCancel::DISALLOW;
}

int RenderManager::CancelChoice()
{
    m_ChoiceBox.m_IsOpen = false;

    switch(m_ChoiceBox.GetCancelBehaviour())
    {
        case lcf::Choices::ChoiceCaseOnCancel::CHOICE_1:
            return 1;
        case lcf::Choices::ChoiceCaseOnCancel::CHOICE_2:
            return 2;
        case lcf::Choices::ChoiceCaseOnCancel::CHOICE_3:
            return 3;
        case lcf::Choices::ChoiceCaseOnCancel::CHOICE_4:
            return 4;
        // TODO: How to handle this case?
        case lcf::Choices::ChoiceCaseOnCancel::OWN_BRANCH:
            return -1;
    }

    // Error case
    return -1;
}

int RenderManager::CloseChoice()
{
    m_ChoiceBox.m_IsOpen = false;
    return m_ChoiceBox.GetChoiceIndex();
}

// InputNumber
void RenderManager::OpenNumberInput(uint8_t numOfDigits) 
{
    const sf::View& view = m_Window.getView();

    m_InputBox.m_IsOpen = true;
    m_InputBox.Setup(view, numOfDigits);
}

void RenderManager::ChangeSelectedNumber(int delta) 
{
    m_InputBox.IncreaseDigit(delta);
}

void RenderManager::MoveSelectedNumber(int delta) 
{
    m_InputBox.MoveDigit(delta);
}

int RenderManager::CloseNumberInput()
{
    m_InputBox.m_IsOpen = false;
    return m_InputBox.GetNumber();
}

void RenderManager::PutPixel(int x, int y, sf::Color color)
{
    assert(x >= 0 && x < m_PictureGPUTexture.getSize().x 
        && y >= 0 && y < m_PictureGPUTexture.getSize().y);

    m_PictureCPUTexture.setPixel(x, y, color);
}

}; // namespace rpgenv
