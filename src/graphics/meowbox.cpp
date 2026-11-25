#include <BPAST/graphics/meowbox.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <cmath>
#include <iostream>
#include <vector>

namespace bpast {

namespace {

// a LOT of hardcoded shit in here but idk what else to do rn

const char* skyvert = R"(#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 dir;
uniform mat4 view;
uniform mat4 projection;
void main() {
    dir = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
)";

const char* skyfrag = R"(#version 330 core
in vec3 dir;
out vec4 FragColor;
uniform samplerCube sky;
void main() {
    FragColor = texture(sky, dir);
}
)";

const float cubeVerts[] = {
    -1.0f,  1.0f, -1.0f,  -1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,   1.0f,  1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,  -1.0f, -1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,   1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,   1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,   1.0f, -1.0f,  1.0f
};

unsigned int compile(GLenum type, const char* src) {
    unsigned int meowder = glCreateShader(type);
    glShaderSource(meowder, 1, &src, nullptr);
    glCompileShader(meowder);

    int ok;
    char log[512];
    glGetShaderiv(meowder, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        glGetShaderInfoLog(meowder, 512, nullptr, log);
        std::cerr << "skybox shader blew up yo: " << log << std::endl;
    }
    return meowder;
}

void setCubeParams() {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

unsigned char toByte(float value) {
    return (unsigned char)(glm::clamp(value, 0.0f, 1.0f) * 255.0f);
}

}

// the cube mesh and the der program (same for both constructors)
void meowbox::setupbox() {
    unsigned int vert = compile(GL_VERTEX_SHADER, skyvert);
    unsigned int frag = compile(GL_FRAGMENT_SHADER, skyfrag);

    meowgram = glCreateProgram();
    glAttachShader(meowgram, vert);
    glAttachShader(meowgram, frag);
    glLinkProgram(meowgram);

    int ok;
    char log[512];
    glGetProgramiv(meowgram, GL_LINK_STATUS, &ok);
    if (!ok) {
        glGetProgramInfoLog(meowgram, 512, nullptr, log);
        std::cerr << "skybox program linking blew up yo: " << log << std::endl;
    }
    glDeleteShader(vert);
    glDeleteShader(frag);

    glGenVertexArrays(1, &meow);
    glGenBuffers(1, &mrow);
    glBindVertexArray(meow);
    glBindBuffer(GL_ARRAY_BUFFER, mrow);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

// from image files
meowbox::meowbox(const std::string& folder, const std::string& ext) {
    setupbox();

    glGenTextures(1, &meowxture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, meowxture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const char* names[6] = {"right", "left", "top", "bottom", "front", "back"};
    unsigned char* data[6] = {};
    int width[6] = {}, height[6] = {}, channels[6] = {};
    bool allGood = true;

    // cubemap faces are not flipped (meowxture turns flipping back on by itself)
    stbi_set_flip_vertically_on_load(false);

    for (int i = 0; i < 6; i++) {
        std::string path = folder + "/" + names[i] + "." + ext;
        data[i] = stbi_load(path.c_str(), &width[i], &height[i], &channels[i], 3);   // always 3 channels
        if (!data[i]) {
            std::cerr << "skybox face isnt really loading " << path << std::endl;
            allGood = false;
        } else if (data[0] && (width[i] != width[0] || height[i] != height[0])) {
            std::cerr << "skybox faces need to be the same size (obviously...): " << path << std::endl;
            allGood = false;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (allGood) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width[i], height[i], 0,
                         GL_RGB, GL_UNSIGNED_BYTE, data[i]);
        } else {
            unsigned char mimi[3] = {255, 0, 255};   // magenta means something went wrong
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 1, 1, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, mimi);
        }
        if (data[i]) stbi_image_free(data[i]);
    }

    setCubeParams();
}

// from three colors, no files needed
meowbox::meowbox(const glm::vec3& top, const glm::vec3& horizon, const glm::vec3& bottom) {
    setupbox();

    glGenTextures(1, &meowxture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, meowxture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const int size = 64;
    std::vector<unsigned char> pixels(size * size * 3);

    for (int face = 0; face < 6; face++) {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                float u = 2.0f * (col + 0.5f) / size - 1.0f;
                float v = 1.0f - 2.0f * (row + 0.5f) / size;

                // how high this pixel looks (1 = straight up, -1 = straight down)
                float y = (face == 2) ? 1.0f : (face == 3) ? -1.0f : v;
                float height = y / std::sqrt(1.0f + u * u + v * v);

                glm::vec3 color = (height >= 0.0f)
                    ? glm::mix(horizon, top, std::sqrt(height))
                    : glm::mix(horizon, bottom, std::sqrt(-height));

                int at = (row * size + col) * 3;
                pixels[at + 0] = toByte(color.r);
                pixels[at + 1] = toByte(color.g);
                pixels[at + 2] = toByte(color.b);
            }
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_RGB, size, size, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    }

    setCubeParams();
}

meowbox::~meowbox() {
    glDeleteTextures(1, &meowxture);
    glDeleteBuffers(1, &mrow);
    glDeleteVertexArrays(1, &meow);
    glDeleteProgram(meowgram);
}

void meowbox::draw(const glm::mat4& view, const glm::mat4& projection) const {
    glDepthFunc(GL_LEQUAL);   // the sky sits at max depth, so it has to pass "equal"

    glUseProgram(meowgram);
    glm::mat4 viewNoMove = glm::mat4(glm::mat3(view));   // drops the camera position, so the sky never gets closer
    glUniformMatrix4fv(glGetUniformLocation(meowgram, "view"), 1, GL_FALSE, glm::value_ptr(viewNoMove));
    glUniformMatrix4fv(glGetUniformLocation(meowgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, meowxture);
    glUniform1i(glGetUniformLocation(meowgram, "sky"), 0);

    glBindVertexArray(meow);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}

}
