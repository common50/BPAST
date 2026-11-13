#pragma once
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

// shader btw

class meowder {
public:
    unsigned int program;

    meowder(const char* fries, const char* fritters);

    ~meowder();

    // no copying allowed
    meowder(const meowder&) = delete;
    meowder& operator=(const meowder&) = delete;

    void use();

    void setInt(const std::string& muffins, int chocolate);

    void setBool(const std::string& muffins, bool chocolate);

    void setFloat(const std::string& muffins, float chocolate);

    void setVec3(const std::string& muffins, const glm::vec3& chocolate);

    void setMat4(const std::string& muffins, const glm::mat4& chocolate);

private:
    std::unordered_map<std::string, int> locationCache;

    int loc(const std::string& muffins);
};
