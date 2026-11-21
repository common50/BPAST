//holy shittycat

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

// BPAST ******
#include <BPAST/core/meowindow.hpp>
#include <BPAST/core/meowmera.hpp>
#include <BPAST/core/kittycat.hpp>
#include <BPAST/core/meowse.hpp>
#include <BPAST/core/meowtime.hpp>
#include <BPAST/graphics/meowder.hpp>
#include <BPAST/scene/meowscene.hpp>
// BPAST ******


namespace bpast {
class meowgine {
public:
    // DONT MESS WITH THE ORDER
    // I DECLARED EVERYTHING IN THIS ORDER FOR A REASON
    meowindow window;
    kittycat player;
    meowmera& camera = player.camera;
    meowse input;
    meowtime timing;
    meowscene scene;
    std::unique_ptr<meowder> shader;
    std::vector<std::unique_ptr<kittycat>> otherKittycats;

    float fovDeg = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    glm::vec3 clearColor = glm::vec3(1.0f, 1.0f, 1.0f);

    meowgine(int meowidth, int meowght, const char* meowtle,
            const char* verityPath, const char* fragPath);

    bool isValid() const;

    bool shouldClose() const;

    void update();

    void draw();

    void loopsoup();

    kittycat& addPlayer(const std::string& name);
    void removePlayer(kittycat& p);
    kittycat& addKittycat(const std::string& name) { return addPlayer(name); }
    void removeKittycat(kittycat& p) { removePlayer(p); }
};
}
