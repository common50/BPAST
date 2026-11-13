// self made .obj parser for my other stuff lmk if im messing up with legal (other ppls stuff) cus im
// going to do this inn like the standard way so i might accidentally copy some1 else so pls lmk

// idk what im doinggg ghhghghhghhhhgghgghhgh

#pragma once
#include <vector>

struct Meowdel {
    std::vector<float> vertexData;
    std::vector<unsigned int> indices;
};


Meowdel loadObj(const char* path);

// -common50

// okay i think i fixed the "f 1 2 3" thing lmk if i fucked it up
