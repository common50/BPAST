// graphics engine but i lowkey cheat using opengl and glfw cus im lazy
// be patient and sit still

// 2 lines for functions else ill go insane


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// bpast ******
#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/core/meowmera.hpp>
#include <BPAST/core/meowindow.hpp>
#include <BPAST/core/meowse.hpp>
#include <BPAST/core/meowtime.hpp>
#include <BPAST/graphics/meowder.hpp>
// bpast ******

#ifdef _WIN32
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001;
}
#endif




// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX global vars n straight bars XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// TO DO: remove all this stuff and make vars not global because its bad

// i always keep it neat with the global vars cus i like to know where they are and what they do
// else ill mess up, seriously, i dont know what my problem is when i have messy globals

// functions n stuff can be all over the place idc i can handle that
// but dont mess with my global vars

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

// texture loading and binding and yknow whatever other stuff related to textures
// idk what to name stuff
unsigned int textureThing(const char* path) {
    unsigned int meowxture; // meowwwww
    glGenTextures(1, &meowxture);
    glBindTexture(GL_TEXTURE_2D, meowxture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels; // i couldnt come up with anything :( same with path btw
    unsigned char* meowta = stbi_load(path, &width, &height, &nrChannels, 0);

    if (meowta) {
        std::cout << "loaded " << path << ": " << width << "x" << height << " channels=" << nrChannels << std::endl; // temporary debug print cus im stupid

        GLenum format;
        if (nrChannels == 1) {
            format = GL_RED;
        } else if (nrChannels == 3) {
            format = GL_RGB;
        } else if (nrChannels == 4) {
            format = GL_RGBA;
        } else {
            std::cerr << "woah wtf this is the amount of channels: " << nrChannels << " for " << path << std::endl;
            format = GL_RGB;
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, meowta);
        // couldnt have done that witout param 6
        glGenerateMipmap(GL_TEXTURE_2D); // its so easy
         stbi_image_free(meowta); // else my mem is gonna get caught leaking
    } else {
        std::cerr << "texture loading isnt loading" << path << std::endl; // only thing yall are getting is the path 4 now
        unsigned char magenta[3] = {255, 0, 255}; // is this even magenta?
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, magenta);
    }

    return meowxture;
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

void loopsoup(meowindow& window, meowder& shader, std::vector<MeowObject>& sceneObjects) {
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

        for (MeowObject& obj : sceneObjects) {
            shader.setMat4("meowdel", obj.modelMatrix);
            shader.setBool("huhTexture", obj.useTexture);
            if (obj.useTexture) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, obj.textureID);
            }
            glBindVertexArray(obj.VAO);
            glDrawElements(GL_TRIANGLES, obj.indexCount, GL_UNSIGNED_INT, 0);
        }

        window.swapBuffers();
        window.pollEvents();

        if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
            window.requestClose();
        }
    }
}


// "free my boy ram he aint do nun"
void cleanupcrew(std::vector<MeowObject>& sceneObjects) {
    for (MeowObject& obj : sceneObjects) {
        glDeleteVertexArrays(1, &obj.VAO);
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

    unsigned int meowndTexture = textureThing("assets/textures/garden.jpg");

    std::vector<MeowObject> sceneObjects;
    sceneObjects.push_back(loadSceneObject("assets/models/rainbowcube.obj", false, 0));
    sceneObjects.push_back(loadSceneObject("assets/models/meownd.obj", true, meowndTexture));
    sceneObjects.push_back(loadSceneObject("assets/models/mittest.obj", false, 0));

    sceneObjects[2].modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

    // versioj check cus ppl tend to mess version stuff up and i alwaus need to fix it for them
    std::cout << "current version " << glGetString(GL_VERSION) << std::endl;

    loopsoup(window, meowder, sceneObjects);

    cleanupcrew(sceneObjects);

    return 0;
}

// TO DO:
// * fix up the loopsoup thing so that we dont have the entire codebase in there
// * split the codebase into smaller chunks (so like multiple files)
// * find out what other stuff i need to fix b4 adding new features to this mess
// * use less globals
// * use classes

// -common50
