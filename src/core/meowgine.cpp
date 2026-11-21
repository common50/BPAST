#include <BPAST/core/meowgine.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace bpast {

namespace {
void syncKittycat(meowscene& scene, const kittycat& who) {
    if (who.body < 0) return;
    auto it = scene.objects.find(who.body);
    if (it == scene.objects.end()) return;

    it->second.transform.position = who.camera.paws;
    it->second.transform.rotation.y = -(who.camera.myaw + 90.0f);   // imma assume that the model faces -z at 0
}
}

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
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) window.requestClose();

    player.move(
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
    window.getCursorPos(meowsorX, meowsorY);
    if (input.processInput((float)meowsorX, (float)meowsorY)) {
        player.look(input.deltaXmeowse, input.deltaYmeowse);
    }

    syncKittycat(scene, player);
    for (auto& other : otherKittycats) syncKittycat(scene, *other);
}

void meowgine::draw() {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->setMat4("miew", camera.getViewMatrix());
    shader->setMat4("meowjection", glm::perspective(glm::radians(fovDeg), window.aspectRatio(), nearPlane, farPlane));

    shader->setVec3("viewPaws", camera.paws);

    scene.draw(*shader);

    window.swapBuffers();
}

void meowgine::loopsoup() {
    while (!shouldClose()) {
        update();
        draw();
    }
}

kittycat& meowgine::addPlayer(const std::string& name) {
    otherKittycats.push_back(std::make_unique<kittycat>(name));
    return *otherKittycats.back();
}

void meowgine::removePlayer(kittycat& p) {
    for (auto it = otherKittycats.begin(); it != otherKittycats.end(); ++it) {
        if (it->get() == &p) {
            otherKittycats.erase(it);
            return;
        }
    }
}
}
