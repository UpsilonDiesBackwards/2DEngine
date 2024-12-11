
#include "engine/archetypes/entity.h"

Entity::Entity(const std::string &name, EntityFlags flags, const Renderable &renderable, glm::vec2 position)
    : name(name), flags(flags), renderable(renderable), position(position) {
}

glm::vec2 Entity::getPosition() {
    return glm::vec2();
}

glm::vec2 Entity::setPosition(glm::vec2 newPos) {
    position = newPos;
}

void Entity::Render() {
    if (ACTIVE && RENDERABLE) {
        renderable.Draw();
    }
}
