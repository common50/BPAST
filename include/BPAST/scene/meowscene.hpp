#pragma once
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/scene/lightstuff.hpp>
#include <BPAST/graphics/meowder.hpp>

namespace bpast {

using meowshCache = std::unordered_map<std::string, std::weak_ptr<meowsh>>;

// idrc anymore

class meowscene {
public:
    std::map<int, meowObject> objects;
    std::vector<Light> lights;
    glm::vec3 ambient{0.05f};
    glm::vec3 clearColor{1.0f};

    meowscene();
    explicit meowscene(std::shared_ptr<meowshCache> sharedMeowsheCache);
    meowscene(const meowscene&) = delete;
    meowscene& operator=(const meowscene&) = delete;

    // i don wanna guess pos
    int add(const char* soup, bool taxi = false, unsigned int biscuits = 0);
    void remove(int id);
    meowObject& get(int meow) { return objects.at(meow); }

    int addLight(const DirectionalLight& l);
    int addLight(const PointLight& l);
    Light& light(int id) { return lights[id]; }

    void draw(meowder& shady);

private:
    std::shared_ptr<meowshCache> meshCache;
    int nextId = 0;
};

}
