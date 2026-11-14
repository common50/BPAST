#pragma once
#include <unordered_map>
#include <BPAST/core/meowindow.hpp>

namespace bpast {
class meowse {
public:
    bool cursorLocked;
    bool firstmeowse;
    float lastXmeowse;
    float lastYmeowse;

    float deltaXmeowse;
    float deltaYmeowse;

    meowse();

    bool processInput(float pancakes, float waffles);

    void toggleCursorLock(meowindow& muffins);

    bool keyPressed(meowindow& muffins, int bread);

private:
    std::unordered_map<int, bool> whiskers;

};
}
