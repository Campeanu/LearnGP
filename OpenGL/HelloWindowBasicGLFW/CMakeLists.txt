cmake_minimum_required(VERSION 3.8)

set(This HelloWindowBasicGLFW)

set(SOURCES
    src/main.cpp
)

# -------------------------------------------
# How to add a directory to include path: 
# include_directories(${variable}/include)

# How to add a directory to link path: 
# link_directories(${variable}/lib)
# -------------------------------------------


# How to add compilation definitions:
# add_compile_definitions(difinition)
# add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)
add_compile_definitions(GLEW_STATIC)

# How to set an output path for an executable file  
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# executable
add_executable(${This} ${SOURCES})

# library
# add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${This} PUBLIC
#   GLAD
#   ImGUI
    GLEW
    glfw
    opengl32
)

# target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Applications
)