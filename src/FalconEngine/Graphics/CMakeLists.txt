cmake_minimum_required(VERSION 3.1)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Dependency.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Platform.cmake)
include(${FALCON_ENGINE_ROOT_DIR}/cmake/Target.cmake)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SOURCE_FILES *.cpp)
file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SHADER_FILES *.glsl)

add_library(
    FalconEngine.Graphics                  # Name
    ${FALCON_ENGINE_LIBRARY_TYPE} 	       # Type
    ${FALCON_ENGINE_GRAPHICS_SOURCE_FILES} # Source
    ${FALCON_ENGINE_GRAPHICS_SHADER_FILES})

set(FALCON_ENGINE_GRAPHICS_EXTRA_LIBRARY_FILES
    ${GL_LIBRARY_FILE}
    ${GLEW_LIBRARY_FILE}
    ${GLFW_LIBRARY_FILE}
    )

target_link_libraries(FalconEngine.Graphics ${FALCON_ENGINE_GRAPHICS_EXTRA_LIBRARY_FILES}
    FalconEngine.Core 
    FalconEngine.Math)

fe_add_export_definition(Graphics)
fe_add_import_definition("Core;Math")
fe_set_target_folder(FalconEngine.Graphics "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Graphics)

source_group("Shader Files" FILES ${FALCON_ENGINE_GRAPHICS_SHADER_FILES})

# Rebuild shader folders
assert_defined(FALCON_ENGINE_RUNTIME_OUTPUT_DIR)

file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shaders")
file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shaders")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shaders")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shaders")
