#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "engine/gui/imgui/sceneheirarchy.h"
#include "engine/application/application.h"
#include "imgui.h"

void SceneHierarchy::Show() {
    Application& app = Application::GetInstance();
    auto currentScene = app.sceneManager->GetCurrentScene();

    ImGui::Begin("Heirarchy", nullptr);

    // Create a new entity
    static bool showCreateEntityPopup = false;
    static char newNameBuffer[32] = "New Entity";

    if (ImGui::BeginPopupContextWindow("CreateEntityMenu", ImGuiPopupFlags_MouseButtonRight)) {
        if (ImGui::MenuItem("Create Entity")) {
            showCreateEntityPopup = true;
        }
        ImGui::EndPopup();
    }

    if (showCreateEntityPopup) { ImGui::OpenPopup("Entity Name"); }

    if (ImGui::BeginPopupModal("Entity Name", &showCreateEntityPopup, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Enter name: ");
        ImGui::InputText("##EntityName", newNameBuffer, sizeof(newNameBuffer));

        if (ImGui::Button("Cancel")) {
            showCreateEntityPopup = false;
            memset(newNameBuffer, 0, sizeof(newNameBuffer));
        }

        ImGui::SameLine();

        if (ImGui::Button("Create")) {
            Transform defaultTransform;
            Entity *newEntity = new Entity(newNameBuffer, EntityFlags::NONE, defaultTransform);
            currentScene->AddEntity(std::shared_ptr<Entity>(newEntity));

            showCreateEntityPopup = false;
            memset(newNameBuffer, 0, sizeof(newNameBuffer));
        }
        ImGui::EndPopup();
    }

    for (size_t i = 0; i < currentScene->GetEntities().size(); i++) {
        auto entity= currentScene->GetEntities()[i];

        ImGui::PushID(static_cast<int>(i));

        if (ImGui::TreeNode(entity->name.c_str())) {
            // TRANSFORM
            if (ImGui::InputFloat2("Position", &entity->transform.pos[0])) {
                entity->UpdateModelMatrix();
            }
            if (ImGui::InputFloat2("Rotation", &entity->transform.eulerRot[0])) {
                entity->UpdateModelMatrix();
            }
            if (ImGui::InputFloat2("Scale", &entity->transform.scale[0])) {
                entity->UpdateModelMatrix();
            }

            ImGui::Separator();

            // FLAGS

            if (ImGui::CollapsingHeader("Flags")) {
                static bool showFlagPopup = false;
                static EntityFlags selectedFlag = RENDERABLE;

                if (ImGui::Button("Add New Flag")) {
                    showFlagPopup = true;
                }

                if (showFlagPopup) {
                    ImGui::OpenPopup("Select Flag");
                    if (ImGui::BeginPopup("Select Flag")) {
                        for (i = 0; i < 5; i++) {
                            EntityFlags flag = static_cast<EntityFlags>(1 << i);
                            const char* name = nullptr;

                            switch (flag) {
                                case ACTIVE: name = "ACTIVE"; break;
                                case HAS_BOUNDS: name = "HAS_BOUNDS"; break;
                                case PLAYER_CONTROLLED: name = "PLAYER_CONTROLLED"; break;
                                case RENDERABLE: name = "RENDERABLE"; break;
                                default: name = "NONE"; break;
                            }

                            if (ImGui::Selectable(name)) {
                                entity->flags = static_cast<EntityFlags>(entity->flags | flag);
                                showFlagPopup = false;
                            }
                        }
                        ImGui::EndPopup();
                    }
                }

                for (int i = 0; i < 5; ++i) {
                    EntityFlags flag = static_cast<EntityFlags>(1 << i);

                    if (entity->flags & flag) {
                        const char* name = nullptr;

                        switch (flag) {
                            case ACTIVE: name = "ACTIVE"; break;
                            case HAS_BOUNDS: name = "HAS_BOUNDS"; break;
                            case PLAYER_CONTROLLED: name = "PLAYER_CONTROLLED"; break;
                            case RENDERABLE: name = "RENDERABLE"; break;
                            default: name = ""; break;
                        }

                        bool flagSet = (entity->flags & flag) != 0;
                        if (ImGui::Checkbox(name, &flagSet)) {
                            if (flagSet) {
                                entity->flags = static_cast<EntityFlags>(entity->flags | flag);
                            } else {
                                entity->flags = static_cast<EntityFlags>(entity->flags & ~flag);
                            }
                        }
                    }
                }
            }

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
    ImGui::End();
}
