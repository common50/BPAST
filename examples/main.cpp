// graphics engine but i lowkey cheat using opengl and glfw cus im lazy
// be patient and sit still

// 2 lines for functions else ill go insane

#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <BPAST/core/meowgine.hpp>
#include <BPAST/graphics/meowxture.hpp>

using namespace bpast;

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
}
#endif


int main() {
    meowgine meowgine(800, 600, "BPAST", "assets/shaders/mttns.vert", "assets/shaders/mttns.frag");
    if (!meowgine.isValid()) return -1;

    //versioj check cus ppl always tend to mess this up and i need to fix it for them and i dont want to do that
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    meowxture meowtex("assets/textures/garden.jpg");

    meowgine.camera.paws = glm::vec3(0.0f, 0.0f, 3.0f);

    meowgine.scene.add("assets/models/rainbowcube.obj");
    meowgine.scene.add("assets/models/meownd.obj", true, meowtex.id);
    int mittsCUS = meowgine.scene.add("assets/models/mittest.obj");
    meowgine.scene.get(mittsCUS).modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

    while (!meowgine.shouldClose()) {
        meowgine.update();
        meowgine.draw();
    }

    return 0;
}

// woah its so much cleaner now wthhh

// -common50
