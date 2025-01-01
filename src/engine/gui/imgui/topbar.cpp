//
// Created by tayler on 12/12/24.
//

#include "engine/gui/imgui/topbar.h"
#include "imgui.h"
#include "engine/gui/stylemanager.h"

void TopBar::Show(StyleManager* styleManager) {
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
            static bool showStyleEditor = false;
            if (ImGui::MenuItem("Style Editor")) {
                ImGui::ShowStyleEditor();
            }
            if (ImGui::BeginPopup("Style Editor")) {
                showStyleEditor = !showStyleEditor;
                ImGui::EndPopup();
            }
            if (showStyleEditor) {
                ImGui::Begin("Style Editor", &showStyleEditor);
                ImGui::ShowStyleEditor();
                ImGui::End();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Save Layout")) {
                styleManager->SaveStyle();

                if (ImGui::BeginPopup(nullptr, ImGuiWindowFlags_Popup)) {
                    ImGui::Text("Saved editor layout");
                    ImGui::EndPopup();
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
