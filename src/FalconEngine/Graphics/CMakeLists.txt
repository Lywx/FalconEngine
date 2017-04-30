cmake_minimum_required(VERSION 3.0)

include(${FALCON_ENGINE_ROOT_DIR}/cmake/Compiler.cmake)
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

# TODO(Wuxiang): Add Qt configuration.
if (FALCON_ENGINE_PLATFORM_WINDOWS)
    set(FALCON_ENGINE_GRAPHICS_LIBRARY_LINKED_EXTRA
        ${FALCON_ENGINE_GRAPHICS_LIBRARY_LINKED_EXTRA} assimp glew32sd glfw3 opengl32)
elseif (FALCON_ENGINE_PLATFORM_LINUX)
    set(FALCON_ENGINE_GRAPHICS_LIBRARY_LINKED_EXTRA
        ${FALCON_ENGINE_GRAPHICS_LIBRARY_LINKED_EXTRA} assimp dl GL GLEW glfw3 X11)
endif()

target_link_libraries(FalconEngine.Graphics
    FalconEngine.Content
    # FalconEngine.Content
    ${FALCON_ENGINE_GRAPHICS_LIBRARY_LINKED_EXTRA})

fe_set_target_folder(FalconEngine.Graphics "FalconEngine Library Targets")
fe_set_target_output(FalconEngine.Graphics)

source_group("Shader Files" FILES ${FALCON_ENGINE_GRAPHICS_SHADER_FILES})

# Rebuild shader folders
assert_defined(FALCON_ENGINE_RUNTIME_OUTPUT_DIR)

file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shaders")
file(REMOVE_RECURSE "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shaders")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Debug/Content/Shaders")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${FALCON_ENGINE_RUNTIME_OUTPUT_DIR}/Release/Content/Shaders")
