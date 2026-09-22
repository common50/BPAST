#include <glad/glad.h>
#include "obj-pawrser.hpp"

// mess with gpu buffers and vertex arrays
// legit just standard opengl stuff
void GPUseless(Meowdel& model, unsigned int& meow, unsigned int& mrow, unsigned int& pancake) {
    // VAO n VBO n EBO part if you didnt notice

    glGenVertexArrays(1, &meow); // 1 vao pls
    glGenBuffers(1, &mrow); // 1 vbo pls
    glGenBuffers(1, &pancake); // 1 ebo pls

    glBindVertexArray(meow);
    glBindBuffer(GL_ARRAY_BUFFER, mrow);
    glBufferData(GL_ARRAY_BUFFER, model.vertexData.size() * sizeof(float), model.vertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pancake);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), model.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
