cmake_minimum_required(VERSION 3.8)

# All other libraries can be pulled in without further configuration.
# OpenGL:
add_subdirectory(vendor)

# Applications:

# This project contain a basic window that is created using only GLFW
add_subdirectory(HelloWindowBasicGLFW)

# This project contain a window that is created using GLFW and GLAD
add_subdirectory(HelloWindowWithGLAD)

# Hello triangle !!! The process of drawing a triangle in moder OpenGl
add_subdirectory(HelloTriangle)

# Shaders ... In this project i will learn about shaders and how did they work.
add_subdirectory(Shaders)