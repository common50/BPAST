// graphics engine but i lowkey cheat using opengl and glfw cus im lazy
// be patient and sit still

// 2 lines for functions else ill go insane

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// bpast ******
#include <BPAST/core/meowmera.hpp>
#include <BPAST/core/meowindow.hpp>
#include <BPAST/core/meowse.hpp>
#include <BPAST/core/meowtime.hpp>
#include <BPAST/graphics/meowder.hpp>
#include <BPAST/graphics/meowxture.hpp>
#include <BPAST/scene/meowscene.hpp>
// bpast ******

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
}
#endif




// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX global vars n straight bars XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// TO DO: remove all this stuff and make vars not global because its bad

// fyi there used to be like 30 globals in here when this was still a demo

    // camera stuff ----------------------------------------
    meowmera meowmera;

    // mouse stuff -----------------------------------------
    meowse meowse;

    // keyboard stuff --------------------------------------
    bool crashLightOn = true;



    // frame timing stuff ---------------------------------
    meowtime meowtime;

// """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""





// mouse stuff
void meowseCB(GLFWwindow* window, double xpawsin, double ypawsin) {
    if (meowse.processInput((double)xpawsin, (double)ypawsin)) {
        meowmera.chasingMice(meowse.deltaXmeowse, meowse.deltaYmeowse);
    }
}


void toggleKeys(meowindow& window) {
    if (meowse.keyPressed(window, GLFW_KEY_TAB)) {
        meowse.toggleCursorLock(window);
    }
    if (meowse.keyPressed(window, GLFW_KEY_F)) {
        crashLightOn = !crashLightOn;
    }
}


void meowmeraMove(meowindow& window, float deltaTime) {
    meowmera.meowmeraMove(
        window.isKeyPressed(GLFW_KEY_W),
        window.isKeyPressed(GLFW_KEY_S),
        window.isKeyPressed(GLFW_KEY_A),
        window.isKeyPressed(GLFW_KEY_D),
        window.isKeyPressed(GLFW_KEY_SPACE),
        window.isKeyPressed(GLFW_KEY_LEFT_CONTROL),
        window.isKeyPressed(GLFW_KEY_LEFT_SHIFT),
        deltaTime
    );
}

void loopsoup(meowindow& window, meowder& shader, meowscene& meowscene) {
    while (!window.shouldClose()) {
        meowtime.update();
        toggleKeys(window);
        meowmeraMove(window, meowtime.deltaTime);

        glClearColor(0.15f, 0.25f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 miew = meowmera.getViewMatrix();
        glm::mat4 meowjection = glm::perspective(glm::radians(45.0f), window.aspectRatio(), 0.1f, 100.0f);

        shader.setMat4("miew", miew);
        shader.setMat4("meowjection", meowjection);

        shader.setVec3("lightPaws", meowmera.paws);
        shader.setVec3("lightDir", meowmera.front);
        shader.setVec3("lightCol", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("viewPaws", meowmera.paws);
        shader.setFloat("meownCutOff", cos(glm::radians(12.5f)));
        shader.setFloat("meowterCutOff", cos(glm::radians(17.5f)));
        shader.setInt("crashLightOn", crashLightOn);

        meowscene.draw(shader);

        window.swapBuffers();
        window.pollEvents();

        if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
            window.requestClose();
        }
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    meowindow window(800, 600, "BPAST");
    if (!window.isValid()) return -1;

    window.setCursorLocked(true);
    window.setCursorPosCallback(meowseCB);

    meowder meowder("assets/shaders/mttns.vert", "assets/shaders/mttns.frag");
    meowder.use();
    meowder.setInt("meowtex", 0);

    meowxture meowndTexture("assets/textures/garden.jpg");

    meowscene meowscene;
    meowscene.add("assets/models/rainbowcube.obj");
    meowscene.add("assets/models/meownd.obj", true, meowndTexture.id);
    int mitts = meowscene.add("assets/models/mittest.obj");
    meowscene.get(mitts).modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    loopsoup(window, meowder, meowscene);

    return 0;
}

// TO DO:
// * fix up the loopsoup thing so that we dont have the entire codebase in there
// * split the codebase into smaller chunks (so like multiple files)
// * find out what other stuff i need to fix b4 adding new features to this mess
// * use less globals
// * use classes

// -common50
