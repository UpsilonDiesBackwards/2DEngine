#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
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

glm::mat4 Camera::GetProjection() {
    float halfWidth = width / glm::abs(zoom);
    float halfHeight = height / glm::abs(zoom);

    float left = position.x - (halfWidth / 2.0f);
    float right = position.x + (halfWidth / 2.0f);
    float bottom = position.y - (halfHeight / 2.0f);
    float top = position.y + (halfHeight / 2.0f);

    std::cout << "Projection bounds: left=" << left
              << " right=" << right
              << " bottom=" << bottom
              << " top=" << top
              << std::endl;

    glm::mat4 proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    std::cout << "Projection matrix: " << glm::to_string(proj) << std::endl;

    return proj;
}


glm::vec2 Camera::GetPosition() const {
    return position;
}

float Camera::GetZoom() const {
    return zoom;
}