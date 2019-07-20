cmake_minimum_required(VERSION 3.8)

set(This HelloTriangle)

set(SOURCES 
    src/main.cpp
)

add_executable(${This} ${SOURCES})

target_link_libraries(${This} PUBLIC 
    GLAD
    glfw
    opengl32
)

set_target_properties(${This} PROPERTIES 
    FOLDER Applications
)