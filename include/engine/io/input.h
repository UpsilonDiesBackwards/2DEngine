//
// Created by tayler on 24/12/24.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <functional>
#include <map>
#include "inputmanager.h"

class InputManager;

class Input {
public:
    Input(InputManager* inputManager);

    void BindKey(int key, std::function<void()> action);

    void Update();
private:
    InputManager* inputManager;
    std::map<int, std::function<void()>> keybinds;
};


#endif //ENGINE_INPUTMANAGER_H
