
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include "engine/archetypes/entity.h"

Entity::Entity(const std::string &name, EntityFlags flags, Transform transform)
    : name(name), flags(flags), transform(transform), renderable(0,0,0,0) {

    renderable.Initialise();

    Render();
}

void Entity::Render() {
    if (RENDERABLE) {
        UpdateModelMatrix();
        renderable.Draw(transform.modelMatrix);
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

void Entity::UpdateModelMatrix() {
    transform.modelMatrix = glm::mat4(1.0f);

    transform.modelMatrix = glm::scale(transform.modelMatrix, glm::vec3(transform.scale, 1.0f));
    transform.modelMatrix = glm::rotate(transform.modelMatrix, glm::radians(transform.eulerRot.x),
                                        glm::vec3(0.0f, 0.0f, 1.0f));
    transform.modelMatrix = glm::translate(transform.modelMatrix, glm::vec3(transform.pos, 0.0f));
}

template<typename... TArgs>
void Entity::addChild(const TArgs &... args) {
    children->emplace_back(std::make_unique<Entity>(args...));
    children->back()->parent = this;
}
