#include "engine/gui/gameview.h"
#include "engine/gui/framebuffer.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"

/*
 * We will use a frame buffer to display a texture in a imgui window. this will allow us to have a detachable
 * view of our game.
 */

GameView::GameView(int width, int height) : width(width), height(height) { framebuffer = new Framebuffer(width, height); }

GameView::~GameView() { delete framebuffer; }

void GameView::Render() {
    framebuffer->Bind();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // SHIT IN THE GAME VIEW

    framebuffer->Unbind();

    ImGui::Begin("Game View", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImVec2 winSize = ImGui::GetContentRegionAvail();
    if (winSize.x != width || winSize.y != height) {
        width = static_cast<int>(winSize.x);
        height = static_cast<int>(winSize.y);
        Resize(width, height);
    }
    ImGui::Image(framebuffer->GetTexture(), winSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void GameView::Resize(int width, int height) {
    this->width = width;
    this->height = height;

    framebuffer->Resize(width, height);
}