#pragma once
#include <glm/glm.hpp>

namespace bpast {

constexpr int kMaxLights = 8;   // must match MAX_LIGHTS in mttns.frag else it will cry


// lowkey most of this bs was made by a friend of mine cus i was too lazy
// so shoutout to him
// idk whats in here tbh
struct DirectionalLight {
    glm::vec3 direction{0.0f, -1.0f, 0.0f};
    glm::vec3 color{1.0f};
    float     intensity = 1.0f;
};

struct PointLight {
    glm::vec3 position{0.0f};
    glm::vec3 color{1.0f};
    float     intensity = 1.0f;
    float     range     = 20.0f;
};


struct Light {
    enum class Type : int { Directional = 0, Point = 1 };

    Type      type      = Type::Point;
    glm::vec3 position  {0.0f};
    glm::vec3 direction {0.0f, -1.0f, 0.0f};
    glm::vec3 color     {1.0f};
    float     intensity = 1.0f;
    float     range     = 20.0f;
};

}
