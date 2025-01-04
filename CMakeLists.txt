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
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_internal.h
        vendor/imgui/backends/imgui_impl_glfw.cpp
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        src/engine/gui/gameview.cpp
        include/engine/gui/gameview.h
        src/engine/gui/framebuffer.cpp
        include/engine/gui/framebuffer.h
        src/engine/graphics/shader.cpp
        include/engine/graphics/shader.h
        src/engine/gui/stylemanager.cpp
        include/engine/gui/stylemanager.h
        src/engine/gui/editview.cpp
        include/engine/gui/editview.h
        src/engine/archetypes/entity.cpp
        include/engine/archetypes/entity.h
        src/engine/graphics/renderable.cpp
        include/engine/graphics/renderable.h
        src/engine/gui/imgui/editorviews.cpp
        include/engine/gui/editorviews.h
        include/engine/gui/imgui/editorviews.h
        src/engine/gui/imgui/topbar.cpp
        include/engine/gui/imgui/topbar.h
        src/engine/gui/imgui/editorviewstatusbar.cpp
        include/engine/gui/imgui/editorviewstatusbar.h
        src/engine/archetypes/camera.cpp
        include/engine/archetypes/camera.h
        src/engine/io/inputmanager.cpp
        include/engine/io/inputmanager.h
        src/engine/io/input.cpp
        include/engine/io/input.h
        src/engine/application/profiler.cpp
        include/engine/application/profiler.h
        src/engine/scene/scene.cpp
        include/engine/scene/scene.h
        src/engine/scene/scenemanager.cpp
        include/engine/scene/scenemanager.h
)

target_link_libraries(engine glfw ${CMAKE_DL_LIBS} GL pthread)