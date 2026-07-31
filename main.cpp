// graphics engine but i lowkey cheat using opengl and glfw cus im lazy and dont want to write my own graphics engine from scratch
// be patient and sit still

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// clutter comment slop just for you because i have nothing better to do and some ppl like it

int main() {
    if (!glfwInit()) {
        std::cerr << "yo glfwInit failed haha good luck" << std::endl; // cus ppl always get angry at me if i dont do err handling
        return -1; // should i make this 0 haha
    }

    // lowkey ripped these from wiki hahaha
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "BPAST", nullptr, nullptr);
    // same reason as above, i should probably do err handling here too
    if (!window) {
        std::cerr << "yo the window isnt working gang helppppp" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed, do better next time i dont hav all day" << std::endl;
        return 1;
    }

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window)) { // who named this dawg
        glClearColor(0.15f, 0.15f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    glfwTerminate(); //mem leaksskskskks
    return 0;
}