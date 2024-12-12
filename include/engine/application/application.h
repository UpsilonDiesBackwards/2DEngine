//
// Created by tayler on 09/12/24.
//

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "GLFW/glfw3.h"
#include "engine/archetypes/entity.h"
#include "engine/gui/framebuffer.h"
#include "engine/gui/gameview.h"
#include "engine/gui/stylemanager.h"
#include "engine/gui/editview.h"

enum PlayState {
    Play, Stop,
};

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void Initialise();
    void Run();
    void Terminate();

    GLFWwindow* getWindow();

    PlayState playState = PlayState::Stop;
    EditView* editView;
    GameView* gameView;
private:
    GLFWwindow* window;
    int width, height;
    const char* title;

    StyleManager* style;
};
#endif //ENGINE_APPLICATION_H
