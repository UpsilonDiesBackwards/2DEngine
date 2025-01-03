
#ifndef ENGINE_RENDERABLE_H
#define ENGINE_RENDERABLE_H

#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/mat4x4.hpp>

class Renderable {
public:
    Renderable(uint VAO, uint VBO, uint EBO, uint texture);
    void Initialise(); // Buffer Setup
    void Draw(const glm::mat4 modelMatrix);
private:
    uint VAO, VBO, EBO;
    uint texture;
    glm::mat4 projectionMatrix;
};


#endif //ENGINE_RENDERABLE_H
