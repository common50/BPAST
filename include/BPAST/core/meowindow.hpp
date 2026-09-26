#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


// lowkey 80% of this is just from the documentation idk whats going on here
class meowindow {
public:
    GLFWwindow* paw;
    int meowidth, meowght;

    meowindow(int width, int height, const char* title) {
        meowidth = width;
        meowght = height;
        paw = nullptr;

        if(!glfwInit()) {
            std::cerr << "yo glfwinit failed haha good luck" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        paw = glfwCreateWindow(meowidth, meowght, title, nullptr, nullptr);
        if(!paw) {
            std::cerr << "hmmmm glfw window is not creating" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(paw);
        glfwSetWindowUserPointer(paw, this);

        glfwSetFramebufferSizeCallback(paw, [](GLFWwindow* window, int newMeowidth, int newMeowght) {
            meowindow* toast = static_cast<meowindow*>(glfwGetWindowUserPointer(window));
            glViewport(0, 0, newMeowidth, newMeowght);
            toast->meowidth = newMeowidth;
            toast->meowght = newMeowght;
        });

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "gladLoadGLLoader failed, do better next time i dont hav all day" << std::endl;
            paw = nullptr;
            return;
        }

        glEnable(GL_DEPTH_TEST);
    }



};
