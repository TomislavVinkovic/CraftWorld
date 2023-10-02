#include "Player.h"
#include "DeltaTime/DeltaTime.h"

Player::Player(Camera camera) : camera(camera) {}

Player::~Player() {}

void Player::moveForward() {
    auto position = camera.getPosition();
    auto direction = camera.getDirection();

    position += DeltaTime::getDeltaTime() * movementSpeed * direction;
    camera.updatePosition(position);
}

void Player::moveBackward() {
    auto position = camera.getPosition();
    auto direction = camera.getDirection();

    position -= DeltaTime::getDeltaTime() * movementSpeed * direction;
    camera.updatePosition(position);
}

void Player::moveLeft() {
    auto position = camera.getPosition();
    auto direction = camera.getDirection();
    auto up = camera.getUpVector();

    position += DeltaTime::getDeltaTime() * movementSpeed * glm::normalize(glm::cross(up, direction));
    camera.updatePosition(position);
}

void Player::moveRight() {
    auto position = camera.getPosition();
    auto direction = camera.getDirection();
    auto up = camera.getUpVector();

    position += DeltaTime::getDeltaTime() * movementSpeed * glm::normalize(glm::cross(direction, up));
    camera.updatePosition(position);
}

void Player::lookAt(float xPosIn, float yPosIn) {
    camera.updateDirection(xPosIn, yPosIn);
}

void Player::updatePosition() {
    camera.updateViewMatrix();
}
