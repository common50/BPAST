#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/graphics/obj-pawrser.hpp>
#include <BPAST/graphics/meowsh.hpp>

namespace bpast {
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
}
