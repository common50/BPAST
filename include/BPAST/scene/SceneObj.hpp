#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <BPAST/graphics/meowsh.hpp>

// lowkey needed to remove that ugly ass comment thingy

namespace bpast {

struct Transform {
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};

    glm::mat4 matrix() const;
};

struct meowterial {
    // imma just hardcode some bullshit and see what happens lowkey
    glm::vec3 color{1.0f};
    unsigned int texture = 0;
    float specular  = 0.5f;
    float shiny = 32.0f;
};

struct meowObject {
    std::shared_ptr<meowsh> mesh;
    Transform transform;
    meowterial  material;
};

}
