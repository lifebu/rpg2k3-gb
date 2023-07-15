#include "RenderManager.h"

#include <iostream>

namespace rpgenv
{

void RenderManager::Init() 
{
    m_Window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "C++ RPG Env", 
        sf::Style::Titlebar | sf::Style::Close);

    // Position window in the middle of the screen.
    auto currentRes = sf::VideoMode::getDesktopMode();
    m_Window.setPosition(sf::Vector2i(
        currentRes.width / 2 - WINDOW_WIDTH / 2, 
        currentRes.height / 2 - WINDOW_HEIGHT / 2));
    
    m_Window.setFramerateLimit(15);
    
    if(!m_Font.loadFromFile(std::string(FONT_PATH)))
    {
        std::cout << "Could not load the font: " << FONT_PATH << std::endl;
        return;
    }

    m_DebugText.setFont(m_Font);
    m_DebugText.setCharacterSize(24);
    m_DebugText.setFillColor(sf::Color::White);

    // Initialize Textbox
    m_TextBox.SetFont(m_Font);

    // Initialize ChoiceBox
    m_ChoiceBox.SetFont(m_Font);

    // Initialize InputBox
    m_InputBox.setFont(m_Font);
}

void RenderManager::PollEvents() 
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
    }
}

void RenderManager::Render() {
    m_Window.clear(sf::Color(128, 0, 128));

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

};
