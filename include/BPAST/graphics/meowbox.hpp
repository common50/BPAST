#pragma once
#include <string>
#include <glm/glm.hpp>

namespace bpast {

class meowbox {
public:
    explicit meowbox(const std::string& folder, const std::string& ext = "jpg");

    meowbox(const glm::vec3& top, const glm::vec3& horizon, const glm::vec3& bottom); // t or b?

    ~meowbox();

    meowbox(const meowbox&) = delete;
    meowbox& operator=(const meowbox&) = delete;

    void draw(const glm::mat4& view, const glm::mat4& projection) const;

private:
    unsigned int  meow= 0;
    unsigned int mrow = 0;
    unsigned int meowxture = 0;
    unsigned int meowgram = 0;

    void setupbox();
};

}
