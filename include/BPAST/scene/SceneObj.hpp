// idk what to name this file

#pragma once
#include <glm/glm.hpp>

  //__________________________________________________________________________________________\\.
 //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\.
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""\\.

struct MeowObject {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int indexCount;
    unsigned int textureID;
    bool useTexture;
    glm::mat4 modelMatrix;
};


MeowObject loadSceneObject(const char* path, bool utex, unsigned int texid);
