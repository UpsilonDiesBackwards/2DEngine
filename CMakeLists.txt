cmake_minimum_required(VERSION 3.28)
project(engine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor/glfw-3.4)

include_directories(vendor/glfw-3.4/include)

add_executable(engine main.cpp)

target_link_libraries(engine glfw ${CMAKE_DL_LIBS} GL pthread)