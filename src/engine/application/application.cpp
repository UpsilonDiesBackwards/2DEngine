//
// Created by tayler on 09/12/24.
//

#include <iostream>
#include <X11/Xutil.h>
#include "glad/glad.h"
#include "engine/application/application.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine/gui/stylemanager.h"

Application::Application(int width, int height, const char *title) :
    window(nullptr), width(width), height(height), title(title) {};

Application::~Application() {
    Terminate();
}

void Application::Initialise() {
    if (!glfwInit()) { // Initialise GLFW
        std::cerr << "Failed to Initialise GLFW!" << std::endl;
        return;
    } else std::cout << "GLFW Initialised" << std::endl;

    window = glfwCreateWindow(width, height, title, NULL, NULL); // Create the main application window
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    } else std::cout << "Window Created" << std::endl;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Initialise GLAD
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    } else std::cout << "GLAD Initialised" << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); // Create ImGui Context
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Load ImGui custom style
    style = new StyleManager("/home/tayler/projects/2DEngine/res/config/style.txt");
    style->LoadStyle();

    glEnable(GL_DEPTH_TEST);

    gameView = new GameView(width, height);
}

void Application::Run() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: EDITOR SHIT
    ImGui::ShowDemoWindow();
    ImGui::ShowStyleEditor();

    gameView->Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Terminate() {
    style->SaveStyle();
    delete gameView;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Application::getWindow() {
    return window;
}