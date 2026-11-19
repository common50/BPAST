#include <BPAST/core/meowindow.hpp>
#include <iostream>
#include <wchar.h>

namespace bpast{
namespace {
int glfwLiveWindows = 0;
}

meowindow::meowindow(int width, int height, const char* title) {
    meowidth = width;
    meowght = height;
    paw = nullptr;

    if(glfwLiveWindows == 0 && !glfwInit()) {
        std::cerr << "yo glfwinit failed haha good luck" << std::endl;
        return;
    }
    ++glfwLiveWindows;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    paw = glfwCreateWindow(meowidth, meowght, title, nullptr, nullptr);
    if(!paw) {
        std::cerr << "hmmmm glfw window is not creating" << std::endl;
        if(--glfwLiveWindows == 0) glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(paw);
    glfwSetWindowUserPointer(paw, this);

    // idk how lambdas work
    glfwSetFramebufferSizeCallback(paw, [](GLFWwindow* window, int newMeowidth, int newMeowght) {
        meowindow* toast = static_cast<meowindow*>(glfwGetWindowUserPointer(window));
        glViewport(0, 0, newMeowidth, newMeowght);
        toast->meowidth = newMeowidth;
        toast->meowght = newMeowght;
    }); // shoutout to lam bda for making this possible in the first place

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed, do better next time i dont hav all day" << std::endl;
        glfwDestroyWindow(paw);
        paw = nullptr;
        if(--glfwLiveWindows == 0) glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);
}

meowindow::~meowindow() {
    if(paw) {
        glfwDestroyWindow(paw);
        paw = nullptr;
        if(--glfwLiveWindows == 0) glfwTerminate();
    }
}
}
