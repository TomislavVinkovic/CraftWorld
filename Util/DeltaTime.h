# pragma once

// this class is a singleton
class DeltaTime {
    private:
        static inline float currentFrame = 0.f;
        static inline float lastFrame = 0.f;
        static inline float deltaTime = 0.f;

    public:
        static void newFrame(float time);

        static inline float getDeltaTime() { return deltaTime; }
};
