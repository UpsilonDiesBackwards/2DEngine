#include <iostream>
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

    // SHIT IN THE GAME VIEW
    Entity *entity = new Entity("entity", EntityFlags::RENDERABLE, glm::vec2(0,0));

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

void GameView::ShowTriangle() {
    float vertices[] = {
            0.0f,  0.5f, 0.0f,  // top vertex
            -0.5f, -0.5f, 0.0f,  // bottom left vertex
            0.5f, -0.5f, 0.0f   // bottom right vertex
    };

    Shader shader("../res/shaders/shader.vert",
                  "../res/shaders/shader.frag");

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