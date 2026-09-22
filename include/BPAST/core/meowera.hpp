#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class meowmera {
public:
    glm::vec3 paws;
    glm::vec3 front;
    glm::vec3 up;

    float myaw;
    float meowch;

    meowmera() {
        paws = glm::vec3(0.0f, 0.0f, 0.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        myaw = -90.0f;
        meowch = 0.0f;
    }
}
