//
// Created by tayler on 24/12/24.
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "engine/archetypes/camera.h"

Camera::Camera(float width, float height, float zoom) : position(0.0f, 0.0f), zoom(zoom), width(width), height(height) {
}

void Camera::Move(float xOffset, float yOffset) {
    position.x += xOffset;
    position.y += yOffset;
}

void Camera::Zoom(float amount) {
    zoom += amount;
    if (zoom < 0.1f) zoom = 0.1f;
}

void Camera::UpdateViewport(float width, float height) {
    width = width;
    height = height;
}

glm::mat4 Camera::GetProjection() const {
    float left = position.x - (width / 2.0f) / zoom;
    float right = position.x + (width / 2.0f) / zoom;
    float bottom = position.y - (height / 2.0f) / zoom;
    float top = position.y + (height / 2.0f) / zoom;


    return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

glm::vec2 Camera::GetPosition() const {
    return position;
}

float Camera::GetZoom() const {
    return zoom;
}