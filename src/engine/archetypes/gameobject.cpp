
#include "engine/archetypes/gameobject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const std::string &name, Sprite *sprite)  :
        name(name), sprite(sprite), position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f) {
}

void GameObject::SetPosition(glm::vec2 newPos) {
    this->position = newPos;
}

void GameObject::SetRotation(float newRot) {
    this->rotation = newRot;
}

void GameObject::SetScale(glm::vec2 newScale) {
    this->scale = newScale;
}

glm::mat4 GameObject::GetTransform() const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(position, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));
    return transform;
}

void GameObject::Render() {
    // TODO: the entire game object system
}