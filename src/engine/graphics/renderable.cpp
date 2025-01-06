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
                        texture(texture),
                        shaderProgram(Shader("../res/shaders/shader.vert", "../res/shaders/shader.frag")) {
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

void Renderable::Draw(glm::mat4 modelMatrix) {
    glBindVertexArray(VAO);

    shaderProgram.Use();

    shaderProgram.SetMat4("projection", *glm::value_ptr(Application::GetInstance().camera->GetProjection()));
    shaderProgram.SetMat4("view", *glm::value_ptr(Application::GetInstance().camera->GetView()));
    shaderProgram.SetMat4("model", *glm::value_ptr(modelMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(rectIndices)/4, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

