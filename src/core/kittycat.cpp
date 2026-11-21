#include <BPAST/core/kittycat.hpp>

namespace bpast {

kittycat::kittycat(const std::string& kittycatName) : name(kittycatName) {}

void kittycat::move(bool forward, bool back, bool left, bool right,
                  bool up, bool down, bool sprint, float dt) {
    camera.meowmeraMove(forward, back, left, right, up, down, sprint, dt,
                        settings.speed, settings.sprintMultiplier);
}

void kittycat::look(float deltaX, float deltaY) {
    camera.chasingMice(deltaX, deltaY, settings.lookNonsense);
}

}
