cmake_minimum_required(VERSION 3.0)

# Set up deployment configuration
option(FALCON_ENGINE_PLATFORM_QT "Using Qt window system" OFF)
option(FALCON_ENGINE_PLATFORM_GLFW "Using GLFW windows system" ON)

# Set up solution root
set(FALCON_ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Falcon Engine root path.")

add_subdirectory(include)
add_subdirectory(src)

# Set up IDE solution
project(FalconEngine CXX)

# Set up IDE project folder
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
