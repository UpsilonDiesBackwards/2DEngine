
#ifndef ENGINE_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "engine/graphics/sprite.h"

class GameObject {
public:
    std::string name;
    Sprite* sprite;
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;

    GameObject(const std::string& name, Sprite* sprite);

    void SetPosition(glm::vec2 newPos);
    void SetRotation(float newRot);
    void SetScale(glm::vec2 newScale);

    glm::mat4 GetTransform() const;

    void Render();
};


#endif //ENGINE_GAMEOBJECT_H
