#include <BPAST/core/meowtime.hpp>
#include <GLFW/glfw3.h>

meowtime::meowtime() {
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

void meowtime::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
