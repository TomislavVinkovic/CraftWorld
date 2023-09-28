cmake_minimum_required(VERSION 3.26)
project(CraftWorld)

set(CMAKE_CXX_STANDARD 17)

include_directories(src vendor vendor/glad Renderer Player Camera Util)

set(SOURCE_FILES
        vendor/glad/glad.c
        vendor/stb_image/stb_image.cpp
        main.cpp
        GLDebug/GLDebug.h
        GLDebug/GLDebug.cpp
        Renderer/Shader/Shader.cpp
        Renderer/Shader/Shader.h
        Camera/Camera.cpp
        Camera/Camera.h
        Player/Player.cpp
        Player/Player.h
        Util/DeltaTime.cpp
        Util/DeltaTime.h
)

add_executable(CraftWorld ${SOURCE_FILES})
target_link_libraries(CraftWorld glfw3 wayland-client m GL GLU)