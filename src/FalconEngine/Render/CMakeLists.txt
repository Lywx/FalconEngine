file(GLOB FALCON_ENGINE_RENDER_SOURCE_FILES *.cpp)

include_directories(${FALCON_ENGINE_INCLUDE_DIR})
link_directories(${FALCON_ENGINE_LIBRARY_DIR})

add_library(FalconEngine.Render STATIC
    ${FALCON_ENGINE_RENDER_SOURCE_FILES})

set_target_properties(FalconEngine.Render PROPERTIES COMPILE_FLAGS "/MDd")

target_link_libraries(FalconEngine.Render 
    glew32sd.lib glfw3.lib opengl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

# Add to Visual Studio filter folder
set_target_properties(FalconEngine.Render PROPERTIES FOLDER "FalconEngine Targets")