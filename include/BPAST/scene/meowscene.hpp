#pragma once
#include <vector>
#include <BPAST/scene/SceneObj.hpp>
#include <BPAST/graphics/meowder.hpp>

namespace bpast{
// idrc anymore

class meowscene {
public:
    std::vector<MeowObject> objects;

    meowscene();

    ~meowscene();

    meowscene(const meowscene&) = delete;
    meowscene& operator=(const meowscene&) = delete;

    // i don wanna guess pos
    int add(const char* soup, bool taxi = false, unsigned int biscuits = 0);

    MeowObject& get(int meow) {
        return objects[meow];
    }

    void draw(meowder& shady);
};
}
