cmake_minimum_required(VERSION 3.5)

project(Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(Engine main.cpp shaderprogram.cpp shaderprogram.h libs.h quad.h quad.cpp engine_maths.h sprite.cpp sprite.h
    Resources/Shaders/simple.vert Resources/Shaders/simple.frag Resources/Shaders/texture.vert Resources/Shaders/texture.frag)
target_link_libraries(Engine "-framework OpenGL" glfw glew soil2-debug)
