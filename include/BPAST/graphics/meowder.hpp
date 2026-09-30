#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

// shader btw

class meowder {
public:
    unsigned int program;

    meowder(const char* fries, const char* fritters) {
        std::string vertsrc = readFile(fries);
        std::string fragsrc = readFile(fritters);

        unsigned int pancakes = compile(GL_VERTEX_SHADER, vertsrc, "vertex");
        unsigned int waffles = compile(GL_FRAGMENT_SHADER, fragsrc, "fragment");

        program = glCreateProgram();
        glAttachShader(program, pancakes);
        glAttachShader(program, waffles);
        glLinkProgram(program);

        int yippee;
        char meowfo[512];
        glGetProgramiv(program, GL_LINK_STATUS, &yippee);
        if (!yippee) {
            glGetProgramInfoLog(program, 512, nullptr, meowfo);
            std::cerr << "program linking blew up yo: " << meowfo << std::endl;
        }

        glDeleteShader(pancakes);
        glDeleteShader(waffles);
    }

    ~meowder() {
        glDeleteProgram(program);
    }

    // no copying allowed
    meowder(const meowder&) = delete;
    meowder& operator=(const meowder&) = delete;

    void use() {
        glUseProgram(program);
    }

    void setInt(const std::string& muffins, int chocolate) {
        glUniform1i(loc(muffins), chocolate);
    }

    void setBool(const std::string& muffins, bool chocolate) {
        glUniform1i(loc(muffins), (int)chocolate);
    }

    void setFloat(const std::string& muffins, float chocolate) {
        glUniform1f(loc(muffins), chocolate);
    }

    void setVec3(const std::string& muffins, const glm::vec3& chocolate) {
        glUniform3f(loc(muffins), chocolate.x, chocolate.y, chocolate.z);
    }

    void setMat4(const std::string& muffins, const glm::mat4& chocolate) {
        glUniformMatrix4fv(loc(muffins), 1, GL_FALSE, glm::value_ptr(chocolate));
    }

private:
    std::unordered_map<std::string, int> locationCache;

    int loc(const std::string& muffins) {
        auto sit = locationCache.find(muffins);
        if (sit != locationCache.end()) return sit->second;

        int chickens = glGetUniformLocation(program, muffins.c_str());
        if (chickens == -1) {
            std::cerr << "shit uniform not foundddd: " << muffins << std::endl;
        }
        locationCache[muffins] = chickens;
        return chickens;
    }

    std::string readFile(const char* woof) {
        std::ifstream meow(woof);
        if (!meow.is_open()) {
            std::cerr << "noooo shader file isnt loading " << woof << std::endl;
            return "";
        }
        std::stringstream butter;
        butter << meow.rdbuf();
        return butter.str();
    }

    unsigned int compile(GLenum meow, const std::string& mrow, const char* mrrr) {
        unsigned int shader = glCreateShader(meow);
        const char* srcPtr = mrow.c_str();
        glShaderSource(shader, 1, &srcPtr, nullptr);
        glCompileShader(shader);

        int success;
        char info[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, info);
            std::cerr << mrrr << " shader blew up yo: " << info << std::endl;
        }
        return shader;
    }
};
