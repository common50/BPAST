#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class meowxture {
public:
    unsigned int id;

    meowxture(const char* icecream) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        int meowidth, meowght, meownels;
        unsigned char* meowta = stbi_load(icecream, &meowidth, &meowght, &meownels, 0);

        if (meowta) {
            std::cout << "loaded " << icecream << ": " << meowidth << "x" << meowght << " channels=" << meownels << std::endl;

            GLenum meowmat;
            if (meownels == 1) {
                meowmat = GL_RED;
            } else if (meownels == 3) {
                meowmat = GL_RGB;
            } else if (meownels == 4) {
                meowmat = GL_RGBA;
            } else {
                std::cerr << "woah wtf this is the amount of channels: " << meownels << " for " << icecream << std::endl;
                meowmat = GL_RGB;
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, meowmat, meowidth, meowght, 0, meowmat, GL_UNSIGNED_BYTE, meowta);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(meowta);
        } else {
            std::cerr << "texture loading isnt loading " << icecream << std::endl;
            unsigned char mimi[3] = {255, 0, 255};
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, mimi);
        }
    }

    ~meowxture() {
        glDeleteTextures(1, &id);
    }

    meowxture(const meowxture&) = delete;
    meowxture& operator=(const meowxture&) = delete;

    void bind(unsigned int pancakes = 0) {
        glActiveTexture(GL_TEXTURE0 + pancakes);
        glBindTexture(GL_TEXTURE_2D, id);
    }
};
