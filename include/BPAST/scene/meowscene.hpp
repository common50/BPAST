#pragma once
#include <vector>
#include <glad/glad.h>
#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/graphics/meowder.hpp>

// idrc anymore

class meowscene {
public:
    std::vector<MeowObject> objects;

    meowscene() {}

    ~meowscene() {
        for (MeowObject& meowbject : objects) {
            glDeleteVertexArrays(1, &meowbject.VAO);
            glDeleteBuffers(1, &meowbject.VBO);
            glDeleteBuffers(1, &meowbject.EBO);
        }
    }

    meowscene(const meowscene&) = delete;
    meowscene& operator=(const meowscene&) = delete;

    // i don wanna guess pos
    int add(const char* soup, bool taxi = false, unsigned int biscuits = 0) {
        objects.push_back(loadSceneObject(soup, taxi, biscuits));
        return (int)objects.size() - 1;
    }

    MeowObject& get(int meow) {
        return objects[meow];
    }

    void draw(meowder& shady) {
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
};
