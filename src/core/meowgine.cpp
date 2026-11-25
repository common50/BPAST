#include <BPAST/core/meowgine.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace bpast {

namespace {
void syncBody(meowscene& scene, const kittycat& who) {
    if (who.body < 0) return;
    auto it = scene.objects.find(who.body);
    if (it == scene.objects.end()) return;

    it->second.transform.position = who.camera.paws;
    it->second.transform.rotation.y = -(who.camera.myaw + 90.0f);
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

    syncBody(*activeScene, player);
    for (auto& other : otherKittycats) syncBody(*activeScene, *other);
}

void meowgine::draw() {
    meowscene& current = *activeScene;

    glClearColor(current.clearColor.r, current.clearColor.g, current.clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(fovDeg), window.aspectRatio(), nearPlane, farPlane);

    shader->use();
    shader->setMat4("miew", view);
    shader->setMat4("meowjection", projection);

    shader->setVec3("viewPaws", camera.paws);

    current.draw(*shader);
    current.drawSky(view, projection);

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

meowscene* meowgine::findScene(const std::string& name) {
    if (name == "default") return &scene;
    auto it = extraScenes.find(name);
    return it == extraScenes.end() ? nullptr : it->second.get();
}

meowscene& meowgine::createScene(const std::string& name) {
    if (meowscene* existing = findScene(name)) {
        std::cerr << "this scene alr exists: " << name << std::endl;
        return *existing;
    }
    std::unique_ptr<meowscene>& slot = extraScenes[name];
    slot = std::make_unique<meowscene>(sharedMeowshCache);
    return *slot;
}

void meowgine::setActiveScene(meowscene& scene) {
    activeScene = &scene;
}

void meowgine::setActiveScene(const std::string& name) {
    meowscene* found = findScene(name);
    if (!found) {
        std::cerr << "no scene named " << name << ", check ur spelling" << std::endl;
        return;
    }
    activeScene = found;
}

void meowgine::removeScene(const std::string& name) {
    auto it = extraScenes.find(name);
    if (it == extraScenes.end()) return;
    if (activeScene == it->second.get()) activeScene = &scene;
    extraScenes.erase(it);
}
}
