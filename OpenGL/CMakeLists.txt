cmake_minimum_required(VERSION 3.8)

# All other libraries can be pulled in without further configuration.
# OpenGL:
add_subdirectory(vendor)

# Applications:

# This contain a basic window that is created using only GLFW
add_subdirectory(HelloWindowBasicGLFW)

# This contain a window that is created using GLFW and GLAD
add_subdirectory(HelloWindowWithGLAD)