
#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <memory>
#include "engine/graphics/renderable.h"

enum EntityFlags {
    ACTIVE = 1 << 0,
    HAS_BOUNDS = 1 << 2,
    PLAYER_CONTROLLED = 1 << 3,
    RENDERABLE = 1 << 4,
};

struct Transform {
    glm::vec2 pos = {0.0f, 0.0f};
    glm::vec2 eulerRot = {0.0f, 0.0f};
    glm::vec2 scale = {1.0f, 1.0f};

    glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct Entity {
public:
    std::string name;
    EntityFlags flags;
    Renderable* renderable;
    Transform transform;

    Entity* parent = nullptr;
    std::vector<std::unique_ptr<Entity>>* children;

    Entity(const std::string& name, EntityFlags flags, Transform* transform);

    glm::vec2 getPosition();
    glm::vec2 setPosition(glm::vec2 newPos);

    glm::vec2 getEulerRot();
    glm::vec2 setEulerRot(glm::vec2 newRot);

    glm::vec2 getScale();
    glm::vec2 setScale(glm::vec2 newScale);

    template<typename... TArgs>
    void addChild(const TArgs&... args);

    void Render();
};

#endif //ENGINE_ENTITY_H
