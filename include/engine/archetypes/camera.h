//
// Created by tayler on 24/12/24.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glm/detail/type_vec1.hpp>
#include <glm/fwd.hpp>
#include <glm/detail/type_vec2.hpp>

class Camera {
public:
    Camera(float width, float height, float zoom = 1.0f);

    void Move(float xOffset, float yOffset);
    void Zoom(float amount);

    void UpdateViewport(float width, float height);

    glm::mat4 GetProjection() const;
    glm::mat4 GetView() const;
    glm::vec2 GetPosition() const;
    float GetZoom() const;
private:
    glm::vec2 position;
    float zoom;
    float width, height;
};


#endif //ENGINE_CAMERA_H
