//
// Created by tayler on 24/12/24.
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "engine/archetypes/camera.h"
#include "engine/application/application.h"

Camera::Camera(float width, float height, float zoom) : position(0.0f, 0.0f), zoom(zoom), width(width), height(height) {
}

void Camera::Move(float xOffset, float yOffset) {
    position.x += xOffset * panSpeed * Application::GetInstance().profiler->GetDeltaTime();
    position.y += yOffset * panSpeed * Application::GetInstance().profiler->GetDeltaTime();
}

void Camera::Zoom(float amount) {
    zoom += amount * Application::GetInstance().profiler->GetDeltaTime();
    if (zoom < -100.0f) zoom = -100.0f;
    if (zoom > 100.0f) zoom = 100.0f;
}

void Camera::UpdateViewport(float newWidth, float newHeight) {
    width = newWidth;
    height = newHeight;
}

glm::mat4 Camera::GetProjection() const {
    float left = position.x - (width / 2.0f) / zoom;
    float right = position.x + (width / 2.0f) / zoom;
    float bottom = position.y - (height / 2.0f) / zoom;
    float top = position.y + (height / 2.0f) / zoom;

    return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

glm::mat4 Camera::GetView() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
}

glm::vec2 Camera::GetPosition() const {
    return position;
}

float Camera::GetZoom() const {
    return zoom;
}