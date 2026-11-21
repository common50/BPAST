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

struct Material {
    glm::vec3 color{1.0f};
    unsigned int texture = 0;
};

struct meowObject {
    std::shared_ptr<meowsh> mesh;
    Transform transform;
    Material  material;
};

}
