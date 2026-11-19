#include <BPAST/scene/meowscene.hpp>
#include <glad/glad.h>
#include <iostream>
#include <string>

namespace bpast {

// i don wanna guess pos
int meowscene::add(const char* soup, bool taxi, unsigned int biscuits) {
    std::shared_ptr<meowsh> mesh = meshCache[soup].lock();
    if (!mesh) {
        mesh = std::make_shared<meowsh>(soup);
        meshCache[soup] = mesh;
    }

    MeowObject obj;
    obj.mesh = mesh;
    if (taxi) obj.material.texture = biscuits;

    int id = nextId++;
    objects[id] = obj;
    return id;
}

void meowscene::remove(int id) {
    objects.erase(id);
}

namespace {
int pushLight(std::vector<Light>& lights, const Light& l) {
    if ((int)lights.size() >= kMaxLights) {
        std::cerr << "noooo too many lights, max is only like " << kMaxLights << std::endl;
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
    for (auto& entry : objects) {
        MeowObject& meowbject = entry.second;
        bool textured = meowbject.material.texture != 0;

        shady.setMat4("meowdel", meowbject.transform.matrix());
        shady.setVec3("materialColor", meowbject.material.color);
        shady.setBool("huhTexture", textured);
        if (textured) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, meowbject.material.texture);
        }
        meowbject.mesh->draw();
    }
}

}
