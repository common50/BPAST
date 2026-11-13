#include <BPAST/scene/meowscene.hpp>
#include <glad/glad.h>
#include <BPAST/graphics/meowder.hpp>

meowscene::meowscene() {}

meowscene::~meowscene() {
    for (MeowObject& meowbject : objects) {
        glDeleteVertexArrays(1, &meowbject.VAO);
        glDeleteBuffers(1, &meowbject.VBO);
        glDeleteBuffers(1, &meowbject.EBO);
    }
}

// i don wanna guess pos
int meowscene::add(const char* soup, bool taxi, unsigned int biscuits) {
    objects.push_back(loadSceneObject(soup, taxi, biscuits));
    return (int)objects.size() - 1;
}

void meowscene::draw(meowder& shady) {
    for (MeowObject& meowbject : objects) {
        shady.setMat4("meowdel", meowbject.modelMatrix);
        shady.setBool("huhTexture", meowbject.useTexture);
        if (meowbject.useTexture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, meowbject.textureID);
        }
        glBindVertexArray(meowbject.VAO);
        glDrawElements(GL_TRIANGLES, meowbject.indexCount, GL_UNSIGNED_INT, 0);
    }
}
