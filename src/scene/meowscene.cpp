#include <BPAST/scene/meowscene.hpp>
#include <glad/glad.h>
#include <BPAST/graphics/meowder.hpp>
#include <iostream>
#include <string>

namespace bpast {
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

namespace {
int pushLight(std::vector<Light>& lights, const Light& l) {
    if ((int)lights.size() >= kMaxLights) {
        std::cerr << "too many lights, max is " << kMaxLights << std::endl;
        return -1;
    }
    lights.push_back(l);
    return (int)lights.size() - 1;
}
}

int meowscene::addLight(const DirectionalLight& l) {
    Light out;
    out.type      = Light::Type::Directional;
    out.direction = l.direction;
    out.color     = l.color;
    out.intensity = l.intensity;
    return pushLight(lights, out);
}

int meowscene::addLight(const PointLight& l) {
    Light out;
    out.type      = Light::Type::Point;
    out.position  = l.position;
    out.color     = l.color;
    out.intensity = l.intensity;
    out.range     = l.range;
    return pushLight(lights, out);
}

void meowscene::draw(meowder& shady) {
    // lights
    shady.setVec3("sceneAmbient", ambient);
    shady.setInt("lightCount", (int)lights.size());
    for (size_t i = 0; i < lights.size(); i++) {
        const Light& l = lights[i];
        std::string base = "lights[" + std::to_string(i) + "].";
        shady.setInt(base + "type", (int)l.type);
        shady.setVec3(base + "position", l.position);
        shady.setVec3(base + "direction", glm::normalize(l.direction));
        shady.setVec3(base + "color", l.color);
        shady.setFloat(base + "intensity", l.intensity);
        shady.setFloat(base + "range", l.range);
    }

    // objects
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
}
