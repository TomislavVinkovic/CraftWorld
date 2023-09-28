#include "DeltaTime.h"

void DeltaTime::newFrame(float time) {
    currentFrame = time;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}