
#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "engine/graphics/renderable.h"

enum EntityFlags {
    ACTIVE = 1 << 0,
    HAS_BOUNDS = 1 << 2,
    PLAYER_CONTROLLED = 1 << 3,
    RENDERABLE = 1 << 4,
};

struct Entity {
public:
    std::string name;
    EntityFlags flags;
    Renderable* renderable;
    glm::vec2 position;

    Entity(const std::string& name, EntityFlags flags, glm::vec2 position);

    glm::vec2 getPosition();
    glm::vec2 setPosition(glm::vec2 newPos);

    void Render();
};

#endif //ENGINE_ENTITY_H
