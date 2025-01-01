#include <iostream>
#include "engine/io/input.h"
#include "engine/io/inputmanager.h"

Input::Input(InputManager *inputManager) : inputManager(inputManager) {
}

void Input::BindKey(int key, KeyEventType eventType, std::function<void()> action) {
    keybinds[{key, eventType}] = action;
}

void Input::Update() {
    inputManager->Update();

    for (const auto& [keyEventPair, action] : keybinds) {
        int key = keyEventPair.first;
        KeyEventType eventType = keyEventPair.second;

        if ((eventType == KEY_DOWN    && inputManager->isKeyDown(key))  ||
            (eventType == KEY_UP      && inputManager->isKeyUp(key))    ||
            (eventType == KEY_PRESSED && inputManager->isKeyPressed(key))) {
            action();
        }
    }
}
