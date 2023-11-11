#include "ImGUIRenderer.h"

#include "cppRPGenv/pch.h"

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
        core::Logger::Get()->Log("Failed to Initialize ImGui", core::LogLevel::GB_PANIC);
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
                           const sf::Time &deltaTime) 
{
    ImGui::SFML::Update(window, deltaTime);
    BuildImGUI(deltaTime);
    ImGui::SFML::Render(window);
}

bool ImGUIRenderer::ShouldExit() const
{
    return m_ExitPressed;
}

// private
void ImGUIRenderer::BuildImGUI(const sf::Time& deltaTime) 
{
    const bool isExpanded = m_LogIsEnabled;
    float verticalSize = isExpanded ? m_ExpandedSize : 0.0f;
    ImGui::SetNextWindowSize(ImVec2(640.0f, verticalSize));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoSavedSettings;
    if(!isExpanded)
    {
        windowFlags |= ImGuiWindowFlags_NoBackground;
    }
    ImGui::Begin("###Menu", nullptr, windowFlags);

    if(ImGui::BeginMenuBar())
    {
        ImGui::MenuItem("Exit (CTRL+Q)", nullptr, &m_ExitPressed);
        ImGui::MenuItem("Log", nullptr, &m_LogIsEnabled);

        int ms = deltaTime.asMilliseconds();
        int fps = (ms > 0) ? 1'000 / ms : 0;
        std::string fpsLabel = "FPS: " + std::to_string(fps);

        ImGui::MenuItem(fpsLabel.c_str());
        ImGui::EndMenuBar();
    }

    if(m_LogIsEnabled)
    {
        const std::vector<std::string>& currentLog = core::Logger::Get()->GetLog();
        for(const auto& logLine : currentLog)
        {
            ImGui::TextWrapped(logLine.c_str());
        }
    }

    ImGui::End();
}


}; // namespace rpgenv
