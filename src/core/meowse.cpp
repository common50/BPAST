#include <BPAST/core/meowse.hpp>
#include <BPAST/core/meowindow.hpp>

namespace bpast {
meowse::meowse() {
    cursorLocked = true;
    firstmeowse = true;
    lastXmeowse = 0.0f;
    lastYmeowse = 0.0f;
    deltaXmeowse = 0.0f;
    deltaYmeowse = 0.0f;
}

bool meowse::processInput(float pancakes, float waffles) {
    if(!cursorLocked) return false;

    if (firstmeowse) {
        lastXmeowse = pancakes;
        lastYmeowse = waffles;
        firstmeowse = false;
    }

    deltaXmeowse = pancakes - lastXmeowse;
    deltaYmeowse = lastYmeowse - waffles;

    lastXmeowse = pancakes;
    lastYmeowse = waffles;

    return true;
}

void meowse::toggleCursorLock(meowindow& muffins) {
    cursorLocked = !cursorLocked;
    muffins.setCursorLocked(cursorLocked);
    if(cursorLocked) {
        firstmeowse = true;
    }
}

bool meowse::keyPressed(meowindow& muffins, int bread) {
    bool isDown = muffins.isKeyPressed(bread);
    bool wasDown = whiskers[bread];
    whiskers[bread] = isDown;
    return isDown && !wasDown;
}
}
