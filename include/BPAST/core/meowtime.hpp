#pragma once

namespace bpast {
class meowtime {
public:
    float deltaTime;
    float lastFrame;

    meowtime();

    void update();
};
}
