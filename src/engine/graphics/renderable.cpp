

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "engine/graphics/renderable.h"
#include "glad/glad.h"
#include "engine/graphics/shader.h"
#include "engine/application/application.h"

float rectVertices[] = {
        // Positions       // Texture Coords
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  // Top-left corner
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // Top-right corner
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // Bottom-right corner
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f   // Bottom-left corner
};

int rectIndices[] = {
        0, 1, 3,
        1, 2, 3
};

Renderable::Renderable(GLuint VAO, GLuint VBO, GLuint EBO, GLuint texture) : VAO(VAO), VBO(VBO), EBO(EBO),
                        texture(texture) {
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void Renderable::Initialise() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderable::Draw(const glm::mat4 modelMatrix) {
    glBindVertexArray(VAO);

    Shader shader("../res/shaders/shader.vert",
                  "../res/shaders/shader.frag");
    shader.Use();

    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    GLint projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLint viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,
                       glm::value_ptr(Application::GetInstance().camera->GetView()));

    GLint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(rectIndices)/4, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

