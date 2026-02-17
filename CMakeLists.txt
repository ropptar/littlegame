cmake_minimum_required(VERSION 4.2)

project(littlegame VERSION 1.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(glad OBJECT external/glad/src/gl.c)
target_include_directories(glad PRIVATE external/glad/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/shaderloader.cpp
    $<TARGET_OBJECTS:glad>)

target_include_directories(${PROJECT_NAME} PRIVATE
    "include"
    "external/glad/include"
)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
    m dl X11
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders
)