#pragma once
#include <glm/glm.hpp>

class meowmera {
public:
    glm::vec3 paws;
    glm::vec3 front;
    glm::vec3 up;

    float myaw;
    float meowch;


    meowmera();


    glm::mat4 getViewMatrix() const;


    void chasingMice(float meoffsetX, float meoffsetY, float nonsense= 0.1f);

    // fyi prsd = pressed cus i dont want long var names they tire out my poor fingers
    void meowmeraMove(float Wprsd, float Sprsd, float Aprsd, float Dprsd,
        float Spaceprsd, float Ctrlprsd, float Shiftprsd, float deltaTime);
};
