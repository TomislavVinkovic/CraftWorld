#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cmath>

class Camera {
    private:
        float screenWidth;
        float screenHeight;

        float mouseSensitivity = 0.1f;

        float lastX;
        float lastY;
        float pitch = 0.f;
        float yaw = -90.f;
        bool firstMouse = true;

        glm::vec3 up;
        glm::vec3 direction;
        glm::vec3 position;

        glm::mat4 view;
        glm::mat4 projection;

    public:
        Camera(int screenWidth, int screenHeight, float fov, float nearPlane, float farPlane, const glm::vec3& position = {0.f, 2.f, 3.f});
        ~Camera() = default;

        // setters
        const glm::mat4& updateViewMatrix();
        const glm::vec3& updatePosition(const glm::vec3& position) { return this->position = position; }
        const glm::vec3& updateDirection(float xPosIn, float yPosIn);

        // getters
        inline const glm::vec3& getPosition() { return position; }
        inline const glm::vec3& getDirection() { return direction; }
        inline const glm::vec3& getUpVector() { return up; }

        inline const glm::mat4& getView() const { return view; }
        inline const glm::mat4& getProjection() const { return projection; }

        inline float getMouseSensitivity() { return mouseSensitivity; }
        inline float getPitch() { return pitch; }
        inline float getYaw() { return yaw; }
        inline float getScreenWidth() { return screenWidth; }
        inline float getScreenHeight() { return screenHeight; }

};