
#include <iostream>
#include "engine/gui/editorviews.h"
#include "imgui.h"
#include "engine/application/application.h"

void EditorViews::Show(Application* application) {
    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_None);
    if (ImGui::BeginTabBar("Views")) {
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 40);
        if (application->playState == PlayState::Play) {
            if (ImGui::Button("Stop")) {
                application->playState = PlayState::Stop;
                std::cout << "Stop button clicked!" << std::endl;
            }
        } else {
            if (ImGui::Button("Play")) {
                application->playState = PlayState::Play;
                std::cout << "Play button clicked!" << std::endl;
            }
        }

        if (ImGui::BeginTabItem("Edit")) {
            application->gameView->Render();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game")) {
            application->gameView->Render();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
