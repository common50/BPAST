#pragma once
#include <unordered_map>
#include <BPAST/core/meowindow.hpp>

class meowse {
public:
    bool cursorLocked;
    bool firstmeowse;
    float lastXmeowse;
    float lastYmeowse;

    float deltaXmeowse;
    float deltaYmeowse;

    meowse() {
        cursorLocked = true;
        firstmeowse = true;
        lastXmeowse = 0.0f;
        lastYmeowse = 0.0f;
        deltaXmeowse = 0.0f;
        deltaYmeowse = 0.0f;
    }

    bool processInput(float pancakes, float waffles) {
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

    void toggleCursorLock(meowindow& muffins) {
        cursorLocked = !cursorLocked;
        muffins.setCursorLocked(cursorLocked);
        if(cursorLocked) {
            firstmeowse = true;
        }
    }

    bool keyPressed(meowindow& muffins, int bread) {
        bool isDown = muffins.isKeyPressed(bread);
        bool wasDown = whiskers[bread];
        whiskers[bread] = isDown;
        return isDown && !wasDown;
    }

private:
    std::unordered_map<int, bool> whiskers;

};
