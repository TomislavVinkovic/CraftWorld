#pragma once

#include "glm/glm.hpp"

struct AdjacentChunkPositions{
    void update(int x, int y, int z)
    {
        top      =   {x,     y + 32,  z};
        bottom    =   {x,     y - 32,  z};
        left    =   {x - 32, y,      z};
        right   =   {x + 32, y,      z};
        front   =   {x,     y,      z + 32};
        frontLeft = {x-32, y, z+32};
        frontRight = {x+32, y, z+32};
        back    =   {x,     y,      z - 32};
        backLeft = {x-32, y, z-32};
        frontLeft = {x+32, y, z-32};
    }
    glm::vec3 top;
    glm::vec3 bottom;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 frontLeft;
    glm::vec3 frontRight;
    glm::vec3 back;
    glm::vec3 backLeft;
    glm::vec3 backRight;
};