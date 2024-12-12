
#include <iostream>
#include "engine/archetypes/entity.h"

Entity::Entity(const std::string &name, EntityFlags flags, glm::vec2 position)
    : name(name), flags(flags), position(position) {

    renderable = new Renderable(0,0,0,0);
    renderable->Initialise();
    Render();
}

glm::vec2 Entity::getPosition() {
    return glm::vec2();
}

glm::vec2 Entity::setPosition(glm::vec2 newPos) {
    position = newPos;
}

void Entity::Render() {
    if (RENDERABLE) {
        renderable->Draw();
    }
}
