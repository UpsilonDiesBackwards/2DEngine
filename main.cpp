#include <iostream>
#include "include/engine/application/application.h"

int main() {
    Application application(1920, 1080, "Engine Test");
    application.Initialise();

    application.Run();

    while (!glfwWindowShouldClose(application.getWindow())) {
    }

    application.Terminate();
    return 0;
}
