cmake_minimum_required(VERSION 3.28)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/glfw-3.4)

include_directories(include)
include_directories(vendor)
include_directories(vendor/imgui)
include_directories(vendor/imgui/backends)

add_executable(engine
        main.cpp
        src/vendor/glad/glad.c
        vendor/glad/glad.h
        include/engine/application/application.h
        src/engine/application/application.cpp
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(engine glfw ${CMAKE_DL_LIBS} GL pthread)