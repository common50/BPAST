#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace bpast {
// lowkey 80% of this is just from the documentation idk whats going on here
class meowindow {
public:
    GLFWwindow* paw;
    int meowidth, meowght;

    meowindow(int width, int height, const char* title);

    ~meowindow();
    meowindow(const meowindow&) = delete;
    meowindow& operator=(const meowindow&) = delete;

    bool isValid() const {
        return paw != nullptr;
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(paw);
    }

    void swapBuffers() {
        glfwSwapBuffers(paw);
    }

    void pollEvents() {
        glfwPollEvents();
    }

    // mouse stuff n keys
    void setCursorPosCallback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(paw, callback);
    }

    void setCursorLocked(bool locked) {
        glfwSetInputMode(paw, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    bool isKeyPressed(int key) const {
        return glfwGetKey(paw, key) == GLFW_PRESS;
    }

    void requestClose() {
        glfwSetWindowShouldClose(paw, true);
    }

    float aspectRatio() const {
        return static_cast<float>(meowidth) / static_cast<float>(meowght);
    }

    void getCursorPos(double& stroop, double& wafel) {
        glfwGetCursorPos(paw, &stroop, &wafel);
    }


};
}
