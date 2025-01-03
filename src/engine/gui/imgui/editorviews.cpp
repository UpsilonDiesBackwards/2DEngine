
#include <iostream>
#include "engine/gui/editorviews.h"
#include "imgui.h"
#include "engine/application/application.h"

void EditorViews::Show() {
    Application& application = Application::GetInstance();

    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
    if (ImGui::BeginTabBar("Views")) {
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 40);
        if (application.playState == PlayState::Play) {
            if (ImGui::Button("Stop")) {
                application.playState = PlayState::Stop;
                std::cout << "Stop button clicked!" << std::endl;
            }
        } else {
            if (ImGui::Button("Play")) {
                application.playState = PlayState::Play;
                std::cout << "Play button clicked!" << std::endl;
            }
        }

        if (ImGui::BeginTabItem("Edit")) {
            application.editView->Render();
            Application::GetInstance().editorMode = EditorMode::EDIT;
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game")) {
            application.gameView->Render();
            Application::GetInstance().editorMode = EditorMode::GAME;
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    // Status Bar
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    float status_bar_height = 18.0f;

    ImVec2 p1(windowPos.x, windowPos.y + windowSize.y - status_bar_height);
    ImVec2 p2(windowPos.x + windowSize.x, windowPos.y + windowSize.y);

    draw_list->AddRectFilled(p1, p2, IM_COL32(39, 56, 51, 255));

    ImGui::SetCursorPos(ImVec2(4, ImGui::GetWindowHeight() - status_bar_height));
    ImGui::Text("Cursor Pos: (X: %.2f, Y: %.2f )| Play State: %s | Editor Mode: %s",
                (application.camera->GetPosition()[0]), application.camera->GetPosition()[1],
                (application.playState == PlayState::Play ? "Playing" : "Stopped"),
                (application.editorMode == EditorMode::EDIT ? "Edit" : "Game"));

    ImGui::End();
}
