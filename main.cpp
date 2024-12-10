#include <iostream>
#include "include/engine/application/application.h"

int main() {
    Application application(1920, 1080, "Engine Test");
    application.Initialise();

    while (!glfwWindowShouldClose(application.getWindow())) {
        application.Run();
    }

    application.Terminate();
    return 0;
}
