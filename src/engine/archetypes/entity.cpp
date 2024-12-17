
#include <iostream>
#include "engine/archetypes/entity.h"

Entity::Entity(const std::string &name, EntityFlags flags, Transform* transform)
    : name(name), flags(flags), transform(*transform) {

    renderable = new Renderable(0,0,0,0);
    renderable->Initialise();

    Render();
}

void Entity::Render() {
    if (RENDERABLE) {
        renderable->Draw();
    }
}

glm::vec2 Entity::getPosition() {
    return transform.pos;
}

glm::vec2 Entity::setPosition(glm::vec2 newPos) {
    transform.pos = newPos;
}

glm::vec2 Entity::getEulerRot() {
    return transform.eulerRot;
}

glm::vec2 Entity::setEulerRot(glm::vec2 newRot) {
    transform.eulerRot = newRot;
}

glm::vec2 Entity::getScale() {
    return transform.scale;
}

glm::vec2 Entity::setScale(glm::vec2 newScale) {
    transform.scale = newScale;
}
