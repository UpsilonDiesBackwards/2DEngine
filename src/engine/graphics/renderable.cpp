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
    Initialise();

    shaderProgram.Use();

    glBindVertexArray(VAO);


    shaderProgram.SetMat4("projection",Application::GetInstance().camera->GetProjection());

    glm::mat4 view_mat = glm::mat4(1.0f);
    view_mat = glm::translate(view_mat, glm::vec3(-Application::GetInstance().camera->GetPosition(), 0.0f));
    view_mat = glm::scale(view_mat, glm::vec3(Application::GetInstance().camera->GetZoom(), Application::GetInstance().camera->GetZoom(), 1.0f));

    shaderProgram.SetMat4("view", view_mat);
    shaderProgram.SetMat4("model", modelMatrix);


    glDrawElements(GL_TRIANGLES, sizeof(rectIndices)/4, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

