#pragma once
#include <cmath>
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


    glm::mat4 getViewMatrix() const {
        return glm::lookAt(paws, paws + front, up);
    }


    void chasingMice(float meoffsetX, float meoffsetY, float nonsense= 0.1f) {
        meoffsetX *= nonsense;
        meoffsetY *= nonsense;

        myaw += meoffsetX;
        meowch += meoffsetY;

        if(meowch > 89.0f)
            meowch = 89.0f;
        if(meowch < -89.0f)
            meowch = -89.0f;

        glm::vec3 muffins = glm::vec3(0.0f, 0.0f, 0.0f);
        muffins.x = cos(glm::radians(myaw)) * cos(glm::radians(meowch));
        muffins.y = sin(glm::radians(meowch));
        muffins.z = sin(glm::radians(myaw)) * cos(glm::radians(meowch));

        front = glm::normalize(muffins);
    }

    // fyi prsd = pressed cus i dont want long var names they tire out my poor fingers
    void meowermaMove(float Wprsd, float Sprsd, float Aprsd, float Dprsd,
        float Spaceprsd, float Ctrlprsd, float Shiftprsd, float deltaTime) {

        float fritters = 2.5f * deltaTime; // speed
        if (Shiftprsd) fritters *= 2.5f;

        glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

        if (Wprsd) paws += fritters * flatFront;
        if (Sprsd) paws -= fritters * flatFront;
        if (Aprsd) paws -= glm::normalize(glm::cross(flatFront, up)) * fritters;
        if (Dprsd) paws += glm::normalize(glm::cross(flatFront, up)) * fritters;
        if (Spaceprsd) paws += fritters * up;
        if (Ctrlprsd) paws -= fritters * up;
    }
};
