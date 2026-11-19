#pragma once

namespace bpast {

class meowsh {
public:
    explicit meowsh(const char* path);
    ~meowsh();

    meowsh(const meowsh&) = delete;
    meowsh& operator=(const meowsh&) = delete;

    void draw() const;

private:
    unsigned int meow = 0;      // vao
    unsigned int mrow = 0;      // vbo
    unsigned int pancake = 0;   // ebo
    unsigned int indexCount = 0;
};

}
