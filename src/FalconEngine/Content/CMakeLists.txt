set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

file(GLOB FALCON_ENGINE_CONTENT_SOURCE_FILES *.cpp)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

# Content
add_library(FalconEngine.Content STATIC
    ${FALCON_ENGINE_CONTENT_SOURCE_FILES})

target_link_libraries(FalconEngine.Content 
    glew32sd.lib glfw3.lib 
    opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

set_target_properties(FalconEngine.Content PROPERTIES COMPILE_FLAGS "/MTd")
set_target_properties(FalconEngine.Content PROPERTIES SUFFIX ".lib")
set_target_properties(FalconEngine.Content PROPERTIES FOLDER "FalconEngine Targets")

# Content.Test 
file(GLOB FALCON_ENGINE_CONTENT_TEST_SOURCE_FILES Test/*.cpp)

add_executable(FalconEngine.Content.Test
    ${FALCON_ENGINE_CONTENT_TEST_SOURCE_FILES})

target_link_libraries(FalconEngine.Content.Test FalconEngine.Content
    glew32sd.lib glfw3.lib 
    opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

set_target_properties(FalconEngine.Content.Test PROPERTIES COMPILE_FLAGS "/MTd")
set_target_properties(FalconEngine.Content.Test PROPERTIES SUFFIX ".exe")
set_target_properties(FalconEngine.Content.Test PROPERTIES FOLDER "FalconEngine.Test Target")
