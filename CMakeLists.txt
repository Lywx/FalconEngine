cmake_minimum_required(VERSION 3.2)

set(FALCON_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Path to include folder")
set(FALCON_ENGINE_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib     CACHE PATH "Path to include folder")

message(${FALCON_ENGINE_INCLUDE_DIR})
message(${FALCON_ENGINE_LIBRARY_DIR})

add_subdirectory(include)
add_subdirectory(src)

# Global Solution
project(FalconEngine)

# Visual Studio project folder
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
