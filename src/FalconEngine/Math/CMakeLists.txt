set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

file(GLOB_RECURSE FALCON_ENGINE_MATH_SOURCE_FILES *.cpp)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Math STATIC
    ${FALCON_ENGINE_MATH_SOURCE_FILES})

set_target_properties(FalconEngine.Math PROPERTIES COMPILE_FLAGS "/MTd")
set_target_properties(FalconEngine.Math PROPERTIES SUFFIX ".lib")

target_link_libraries(FalconEngine.Math 
    glew32sd.lib glfw3.lib opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

# Add to Visual Studio filter folder
set_target_properties(FalconEngine.Math PROPERTIES FOLDER "FalconEngine Library Targets")
