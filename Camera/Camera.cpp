#include "Camera.h"

Camera::Camera(
        int screenWidth,
        int screenHeight,
        float fov,
        float nearPlane,
        float farPlane,
        const glm::vec3& position
) : position(position) {

    this->screenWidth = static_cast<float>(screenWidth);
    this->screenHeight = static_cast<float>(screenHeight);

    lastX = this->screenWidth / 2;
    lastY = this->screenHeight / 2;

    direction = glm::vec3(0.f, 0.f, -1.f);
    up = glm::vec3(0.f, 1.f, 0.f);

    view = glm::lookAt(position, position + direction, up);
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

const glm::vec3& Camera::updateDirection(float xPosIn, float yPosIn) {
    if(firstMouse) {
        lastX = xPosIn;
        lastY = yPosIn;
        firstMouse = false;
    }

    float xOffset = xPosIn - lastX;
    float yOffset = lastY - yPosIn;

    lastX = xPosIn;
    lastY = yPosIn;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 newDirection;
    newDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newDirection.y = sin(glm::radians(pitch));
    newDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    return direction = glm::normalize(newDirection);
}

const glm::mat4& Camera::updateViewMatrix() {
    return view = glm::lookAt(position, position + direction, up);
}