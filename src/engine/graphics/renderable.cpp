
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "engine/graphics/renderable.h"
#include "engine/graphics/shader.h"
#include "glad/glad.h"

float rectVertices[] = {
        // Positions       // Texture Coords
        -0.5f,  0.5f, 0.0f,  // Top-left corner   (0.0f, 1.0f)
        0.5f,  0.5f, 0.0f,  // Top-right corner  (1.0f, 1.0f)
        0.5f, -0.5f, 0.0f,  // Bottom-right      (1.0f, 0.0f)
        -0.5f, -0.5f, 0.0f   // Bottom-left       (0.0f, 0.0f)
};


int rectIndices[] = {
        0, 1, 3,
        1, 2, 3
};

Renderable::Renderable(GLuint VAO, GLuint VBO, GLuint EBO, GLuint texture) : VAO(VAO), VBO(VBO), EBO(EBO), texture(texture) {
    perspectiveMatrix = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void Renderable::Initialise() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenVertexArrays(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderable::Draw(const glm::mat4 modelMatrix) {
    glBindVertexArray(VAO);

    Shader shader("../res/shaders/shader.vert",
                  "../res/shaders/shader.frag");
    shader.Use();

    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    GLint modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint perspectiveLoc = glGetUniformLocation(shader.ID, "perspective");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(rectIndices)/4, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

