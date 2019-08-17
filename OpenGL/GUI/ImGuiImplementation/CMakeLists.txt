cmake_minimum_required(VERSION 3.8)

set(This ImGuiImplementation)

set(HEADERS 
    include/ImGui/imgui_impl_glfw.h
    include/ImGui/imgui_impl_opengl3.h
)

set(SOURCES 
    src/imgui_impl_glfw.cpp
    src/imgui_impl_opengl3.cpp
    src/main.cpp
)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)
add_compile_definitions(GLEW_STATIC)

add_executable(${This} ${SOURCES} ${HEADERS})

target_link_libraries(${This} PUBLIC 
    GLAD
    GLEW
    glfw
    ImGUI
    opengl32
)

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Applications
)
