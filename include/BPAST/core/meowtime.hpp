#pragma once
#include <GLFW/glfw3.h>

class meowtime {
public:
    float deltaTime;
    float lastFrame;

    meowtime() {
        deltaTime = 0.0f;
        lastFrame = 0.0f;
    }

    void update() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
};
