#include "engine/gui/gameview.h"
#include "engine/gui/framebuffer.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "engine/graphics/shader.h"
#include "GLFW/glfw3.h"

/*
 * We will use a frame buffer to display a texture in a imgui window. this will allow us to have a detachable
 * view of our game.
 */

GameView::GameView(int width, int height) : width(width), height(height) { framebuffer = new Framebuffer(width, height); }

GameView::~GameView() { delete framebuffer; }

void GameView::Render() {
    framebuffer->Bind();

    glViewport(0, 0, width, height);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // SHIT IN THE GAME VIEW
    ShowTriangle();

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

void GameView::ShowTriangle() {
    float vertices[] = {
            0.0f,  0.5f, 0.0f,  // top vertex
            -0.5f, -0.5f, 0.0f,  // bottom left vertex
            0.5f, -0.5f, 0.0f   // bottom right vertex
    };

    Shader shader("/home/tayler/projects/2DEngine/res/shaders/shader.vert",
                  "/home/tayler/projects/2DEngine/res/shaders/shader.frag");

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}