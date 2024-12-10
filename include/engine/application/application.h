//
// Created by tayler on 09/12/24.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "GLFW/glfw3.h"
#include "engine/gui/framebuffer.h"
#include "engine/gui/gameview.h"

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void Initialise();
    void Run();
    void Terminate();

    GLFWwindow* getWindow();
private:
    GLFWwindow* window;
    int width, height;
    const char* title;

    GameView* gameView;
};
#endif //ENGINE_APPLICATION_H