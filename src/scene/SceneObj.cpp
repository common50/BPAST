#include <BPAST/scene/SceneObj.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bpast {

// every moment is another oppertunity to put glm to work
// and then put it in a class and call it your own
glm::mat4 Transform::matrix() const {
    glm::mat4 m = glm::translate(glm::mat4(1.0f), position);
    m = glm::rotate(m, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m = glm::rotate(m, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m = glm::rotate(m, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    return glm::scale(m, scale);
    // just joking i properly did the license stuff for glm and gave credit
}

}
