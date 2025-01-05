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
#include "engine/gui/imgui/topbar.h"
#include "engine/io/inputmanager.h"
#include "engine/io/input.h"
#include "profiler.h"
#include "engine/archetypes/camera.h"
#include "engine/gui/editorviews.h"
#include "engine/scene/scenemanager.h"
#include "engine/gui/imgui/editor.h"

enum PlayState {
    Play, Stop,
};

enum EditorMode {
    EDIT,
    GAME,
};

class Editor;

class Application {
public:
    static Application& GetInstance(int width = 1920, int height = 1080, const char* title = "Engine") {
        static Application instance(width, height, title);
        return instance;
    }
    ~Application();

    void Initialise();
    void Run();
    void Terminate();

    GLFWwindow* getWindow();
    Camera* getCamera();

    PlayState playState = PlayState::Stop;
    EditorMode editorMode = EditorMode::EDIT;

    Framebuffer* framebuffer;

    Editor* editorGUI;

    EditView* editView;
    GameView* gameView;

    InputManager& inputManager;
    Input input;

    SceneManager* sceneManager;
    Camera* camera;

    StyleManager* styleManager;

    Profiler* profiler;
private:
    Application(int width, int height, const char* title);

    GLFWwindow* window;
    int width, height;
    const char* title;
};
#endif //ENGINE_APPLICATION_H
