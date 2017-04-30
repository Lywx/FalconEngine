cmake_minimum_required(VERSION 3.0)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

file(GLOB_RECURSE FALCON_ENGINE_INPUT_SOURCE_FILES *.cpp)

add_library(
    FalconEngine.Input                   # Name
    ${FALCON_ENGINE_LIBRARY_TYPE} 	     # Type
    ${FALCON_ENGINE_INPUT_SOURCE_FILES}) # Source

# TODO(Wuxiang)
# target_link_libraries(FalconEngine.Input
#     glew32sd.lib glfw3.lib)

fe_set_target_folder(FalconEngine.Input "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Input)
