#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "engine/gui/gameview.h"
#include "engine/gui/framebuffer.h"
#include "imgui/imgui.h"
#include "glad/glad.h"
#include "engine/graphics/shader.h"
#include "engine/graphics/renderable.h"
#include "engine/archetypes/entity.h"
#include "GLFW/glfw3.h"

/*
 * We will use a frame buffer to display a texture in an imgui window. this will allow us to have a detachable
 * view of our game.
 */

GameView::GameView(int width, int height) : width(width), height(height) { framebuffer = new Framebuffer(width, height); }

GameView::~GameView() { delete framebuffer; }

void GameView::Render() {
    framebuffer->Bind();

    float aRatio = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);
    glClearColor(0.49f, 0.73f, 0.70f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // RENDER IN THE GAME VIEW

//    Transform trans;
//    Entity *entity = new Entity("entity", EntityFlags::RENDERABLE, trans);

    framebuffer->Unbind();

    ImVec2 winSize = ImGui::GetContentRegionAvail();
    float wRatio = winSize.x / winSize.y;

    if (winSize.x != width || winSize.y != height) {
        width = static_cast<int>(winSize.x);
        height = static_cast<int>(winSize.y);
        Resize(width, height);
    }

    // Retain Aspect Ratio
    if (wRatio > aRatio) {
        width = static_cast<int>(winSize.y * aRatio);
        height = static_cast<int>(winSize.y);
    } else {
        width = static_cast<int>(winSize.x);
        height = static_cast<int>(winSize.x / aRatio);
    }

    ImGui::Image(framebuffer->GetTexture(), ImVec2(winSize.x, winSize.y), ImVec2(0, 1), ImVec2(1, 0));
}

void GameView::Resize(int width, int height) {
    this->width = width;
    this->height = height;

    framebuffer->Resize(width, height);
}