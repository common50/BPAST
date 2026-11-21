#pragma once
#include <string>
#include <BPAST/core/meowmera.hpp>

namespace bpast {

struct kittycatSettings {
    float speed            = 2.5f;
    float sprintMultiplier = 2.5f;
    float lookNonsense  = 0.1f;
};

class kittycat {
public:
    std::string name;
    meowmera camera;
    kittycatSettings settings;
    int body = -1;

    explicit kittycat(const std::string& playerName = "player");

    void move(bool forward, bool back, bool left, bool right,
              bool up, bool down, bool sprint, float dt);
    void look(float deltaX, float deltaY);
};

}
