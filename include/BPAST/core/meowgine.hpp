//holy shittycat

#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// BPAST ******
#include <BPAST/core/meowindow.hpp>
#include <BPAST/core/meowmera.hpp>
#include <BPAST/core/meowse.hpp>
#include <BPAST/core/meowtime.hpp>
#include <BPAST/graphics/meowder.hpp>
#include <BPAST/scene/meowscene.hpp>
// BPAST ******


class meowgine {
public:
    // DONT MESS WITH THE ORDER
    // I DECLARED EVERYTHING IN THIS ORDER FOR A REASON
    meowindow window;
    meowmera camera;
    meowse input;
    meowtime timing;
    meowscene scene;
    std::unique_ptr<meowder> shader;

    bool crashLightOn = true;
    float fovDeg = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float innerCutDeg = 12.5f;
    float outerCutDeg = 17.5f;
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 clearColor = glm::vec3(1.0f, 1.0f, 1.0f);

    meowgine(int meowidth, int meowght, const char* meowtle,
            const char* verityPath, const char* fragPath)
        : window(meowidth, meowght, meowtle) {
            if (!window.isValid()) return;

            window.setCursorLocked(true);

            shader = std::make_unique<meowder>(verityPath, fragPath);
            shader -> use();
            shader -> setInt("meowtex", 0);

        }

    bool isValid() const{
        return window.isValid() && shader != nullptr;
    }

    bool shouldClose() const {
        return window.shouldClose();
    }

    void update() {
        window.pollEvents();
            timing.update();

        if (input.keyPressed(window, GLFW_KEY_TAB)) input.toggleCursorLock(window);
        if (input.keyPressed(window, GLFW_KEY_F)) crashLightOn = !crashLightOn;
        if (window.isKeyPressed(GLFW_KEY_ESCAPE)) window.requestClose();

         camera.meowmeraMove(
         window.isKeyPressed(GLFW_KEY_W),
            window.isKeyPressed(GLFW_KEY_S),
            window.isKeyPressed(GLFW_KEY_A),
            window.isKeyPressed(GLFW_KEY_D),
            window.isKeyPressed(GLFW_KEY_SPACE),
            window.isKeyPressed(GLFW_KEY_LEFT_CONTROL),
            window.isKeyPressed(GLFW_KEY_LEFT_SHIFT),
            timing.deltaTime
        );

        double meowsorX, meowsorY;
        window.getCursorpos(meowsorX, meowsorY);
        if (input.processInput((float)meowsorX, (float)meowsorY)) {
            camera.chasingMice(input.deltaXmeowse, input.deltaYmeowse);
        }
    }

    void draw() {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        shader->setMat4("miew", camera.getViewMatrix());
        shader->setMat4("meowjection", glm::perspective(glm::radians(fovDeg), window.aspectRatio(), nearPlane, farPlane));

        shader->setVec3("lightPaws", camera.paws);
        shader->setVec3("lightDir", camera.front);
        shader->setVec3("lightCol", lightColor);
        shader->setVec3("viewPaws", camera.paws);
        shader->setFloat("meownCutOff", glm::cos(glm::radians(innerCutDeg)));
        shader->setFloat("meowterCutOff", glm::cos(glm::radians(outerCutDeg)));
        shader->setBool("crashLightOn", crashLightOn);

        scene.draw(*shader);

        window.swapBuffers();
    }
};
