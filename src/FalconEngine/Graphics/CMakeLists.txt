set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

file(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SOURCE_FILES *.cpp)
FILE(GLOB_RECURSE FALCON_ENGINE_GRAPHICS_SHADER_FILES *.glsl)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Graphics STATIC
    ${FALCON_ENGINE_GRAPHICS_SOURCE_FILES}
    ${FALCON_ENGINE_GRAPHICS_SHADER_FILES})
source_group("Shader Files" FILES ${FALCON_ENGINE_GRAPHICS_SHADER_FILES})

# Rebuild shader folders
file(REMOVE_RECURSE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Content/Shaders")
file(COPY ${FALCON_ENGINE_GRAPHICS_SHADER_FILES} DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Content/Shaders")

target_link_libraries(FalconEngine.Graphics 
    glew32sd.lib glfw3.lib opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

set_target_properties(FalconEngine.Graphics PROPERTIES COMPILE_FLAGS "/MTd /Gm /ZI")
set_target_properties(FalconEngine.Graphics PROPERTIES LINK_FLAGS "/INCREMENTAL")
set_target_properties(FalconEngine.Graphics PROPERTIES SUFFIX ".lib")
set_target_properties(FalconEngine.Graphics PROPERTIES FOLDER "FalconEngine Library Targets")

