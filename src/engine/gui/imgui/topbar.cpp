//
// Created by tayler on 12/12/24.
//

#include "engine/gui/imgui/topbar.h"
#include "imgui.h"
#include "engine/gui/stylemanager.h"

void TopBar::Show(StyleManager* styleManager, Profiler* profiler) {
    static bool showStyleEditor = false;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) {
            }
            if (ImGui::MenuItem("Open Project")) {
            }
            if (ImGui::MenuItem("Quit")) {
            }
            ImGui::EndMenu();

        }

        if (ImGui::Button("Save")) {
        }

        if (ImGui::BeginMenu("Settings")) {
            if (ImGui::MenuItem("Style Editor")) {
                showStyleEditor = !showStyleEditor;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Save Layout")) {
                styleManager->SaveStyle();

                ImGui::OpenPopup("LayoutSavePopup");
            }

            if (ImGui::BeginPopup("LayoutSavePopup")) {
                ImGui::Text("Saved editor layout");
                ImGui::EndPopup();
            }
            ImGui::EndMenu();
        }

        float alignRight = ImGui::GetWindowWidth() - 170;
        ImGui::SameLine(alignRight);

        static int fps = 60;
        static float frameTime = 3.28f;

        ImGui::Text("FPS: %d | (%.2f ms)", profiler->GetCurrentFPS(), profiler->GetCurrentFrameTime());

        ImGui::EndMainMenuBar();
    }

    if (showStyleEditor) {
        ImGui::Begin("Style Editor", &showStyleEditor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }
}
