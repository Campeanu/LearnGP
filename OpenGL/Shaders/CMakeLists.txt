cmake_minimum_required(VERSION 3.8)

set(This Shaders)


set(HEADERS 
    include/Shaders/Shader.hpp
)

set(SOURCES 
    src/main.cpp
    src/Shader.cpp
)

set(SHADERS
    res/shaders/3.3.shader.fs
    res/shaders/3.3.shader.vs
)

include_directories(${OpenGL}/vendor)

add_executable(${This} ${SOURCES} ${HEADERS} ${SHADERS})

target_link_libraries(${This} PUBLIC
    GLAD
    glfw
    opengl32
)

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Applications
)