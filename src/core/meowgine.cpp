#include <BPAST/core/meowgine.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

meowgine::meowgine(int meowidth, int meowght, const char* meowtle,
        const char* verityPath, const char* fragPath)
    : window(meowidth, meowght, meowtle) {
        if (!window.isValid()) return;

        window.setCursorLocked(true);

        shader = std::make_unique<meowder>(verityPath, fragPath);
        shader -> use();
        shader -> setInt("meowtex", 0);

    }

bool meowgine::isValid() const{
    return window.isValid() && shader != nullptr;
}

bool meowgine::shouldClose() const {
    return window.shouldClose();
}

void meowgine::update() {
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

void meowgine::draw() {
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

void meowgine::loopsoup() {
    while (!shouldClose()) {
        update();
        draw();
    }
}
