# pragma once


#include "Camera.h"

class Player {
    private:
        Camera camera;

        float movementSpeed = 25.f;

    public:
        Player(Camera camera);
        ~Player();

        // these functions get called as a response to key strokes
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();

        // this function gets called as a
        void lookAt(float xPosIn, float yPosIn);

        /*
         * This function gets called every frame to update the view matrix
        */
        void updatePosition();

        // getters
        const Camera& getCamera() const { return camera; }
        const glm::vec3& getPosition() { return camera.getPosition(); }
};
