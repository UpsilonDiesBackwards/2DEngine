#include <iostream>
#include "engine/io/input.h"
#include "engine/io/inputmanager.h"

Input::Input(InputManager *inputManager) : inputManager(inputManager) {
}

void Input::BindKey(int key, std::function<void()> action) {
    keybinds[key] = action;
}

void Input::Update() {
    inputManager->Update();

    for (const auto& [key, action] : keybinds) {
        if (inputManager->isKeyDown(key)) {
            std::cout << "Key pressed: " << key << std::endl;
            action();
        }
    }
}
