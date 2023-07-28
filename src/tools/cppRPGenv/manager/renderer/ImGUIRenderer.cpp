#include "ImGUIRenderer.h"

#include <cassert>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <core/structure/Logger.h>

namespace rpgenv
{
// public
void ImGUIRenderer::Init(sf::RenderWindow &window) 
{
    if(!ImGui::SFML::Init(window))
    {
        Logger::Get()->Log("Failed to Initialize ImGui", LogLevel::GB_PANIC);
    }
}

void ImGUIRenderer::Shutdown() 
{
    ImGui::SFML::Shutdown();
}

void ImGUIRenderer::ProcessEvent(const sf::Event &event) 
{
    ImGui::SFML::ProcessEvent(event);
}

void ImGUIRenderer::Render(sf::RenderWindow &window,
                           sf::Clock &clock) 
{
    ImGui::SFML::Update(window, clock.restart());
    BuildImGUI();
    ImGui::SFML::Render(window);
}

// private
void ImGUIRenderer::BuildImGUI() 
{
    // TODO: Create own IMGUI Stuff here!
    ImGui::ShowDemoWindow();
}


}; // namespace rpgenv
