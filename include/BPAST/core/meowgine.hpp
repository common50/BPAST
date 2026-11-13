//holy shittycat

#pragma once

#include <memory>
#include <glm/glm.hpp>

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
            const char* verityPath, const char* fragPath);

    bool isValid() const;

    bool shouldClose() const;

    void update();

    void draw();

    void loopsoup();
};
