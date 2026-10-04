// idk what to name this file

#include <glm/glm.hpp>
#include "../graphics/obj-pawrser.hpp"
#include "../graphics/meowsh.hpp"

  //__________________________________________________________________________________________\\
 //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""\\

struct MeowObject {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int indexCount;
    unsigned int textureID;
    bool useTexture;
    glm::mat4 modelMatrix;
};


MeowObject loadSceneObject(const char* path, bool utex, unsigned int texid) {
    Meowdel fries = loadObj(path);

    unsigned int meow, mrow, pancake;
    GPUseless(fries, meow, mrow, pancake);

    MeowObject obj;
    obj.VAO = meow;
    obj.VBO = mrow;
    obj.EBO = pancake;
    obj.indexCount = (unsigned int)fries.indices.size();
    obj.textureID = texid;
    obj.useTexture = utex;
    obj.modelMatrix = glm::mat4(1.0f);

    return obj;
}
