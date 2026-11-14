#pragma once

namespace bpast {
class meowxture {
public:
    unsigned int id;

    meowxture(const char* icecream);

    ~meowxture();

    meowxture(const meowxture&) = delete;
    meowxture& operator=(const meowxture&) = delete;

    void bind(unsigned int pancakes = 0);
};
}
