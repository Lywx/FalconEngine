set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

file(GLOB_RECURSE FALCON_ENGINE_CONTEXT_SOURCE_FILES *.cpp)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

# Content
add_library(FalconEngine.Context STATIC
    ${FALCON_ENGINE_CONTEXT_SOURCE_FILES})

target_link_libraries(FalconEngine.Context 
    glew32sd.lib glfw3.lib 
    opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

set_target_properties(FalconEngine.Context PROPERTIES COMPILE_FLAGS "/MTd")
set_target_properties(FalconEngine.Context PROPERTIES SUFFIX ".lib")
set_target_properties(FalconEngine.Context PROPERTIES FOLDER "FalconEngine Library Targets")
