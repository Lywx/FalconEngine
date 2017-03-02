set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FALCON_ENGINE_ARCHIVE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FALCON_ENGINE_LIBRARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

function(add_sample sampleProject sampleDir)
    file(GLOB FALCON_ENGINE_SAMPLE_FILES ${sampleDir}/*.h ${sampleDir}/*.cpp)

    include_directories(${FALCON_ENGINE_INCLUDE_DIR})
    link_directories(${FALCON_ENGINE_LIBRARY_DIR}
        ${FALCON_ENGINE_RUNTIME_OUTPUT_DIR})

    add_executable(${sampleProject}
        ${FALCON_ENGINE_SAMPLE_FILES})

    if (WIN32)
    set(FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_BINRARY_FILES 
        assimp-vc140-mt.lib
        glew32sd.lib glfw3.lib opengl32.lib kernel32.lib user32.lib gdi32.lib 
        winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib 
        advapi32.lib)
    else()
    message(WARNING "Dependency not available in linux.")
    endif()

    set_target_properties(${sampleProject} PROPERTIES SUFFIX ".exe")
    target_link_libraries(${sampleProject} 
        FalconEngine.Content.lib
        FalconEngine.Context.lib
        FalconEngine.Core.lib
        FalconEngine.Graphics.lib
        FalconEngine.Input.lib
        FalconEngine.Math.lib
        ${FALCON_ENGINE_CONTENT_PIPELINE_EXTRA_BINRARY_FILES})

    set_target_properties(${sampleProject} PROPERTIES COMPILE_FLAGS "/MTd /ZI")
    set_target_properties(${sampleProject} PROPERTIES LINK_FLAGS "/IMPLIB:")
    #set_target_properties(${sampleProject} PROPERTIES LINK_FLAGS "/INCREMENTAL /IMPLIB:")
    set_target_properties(${sampleProject} PROPERTIES FOLDER "FalconEngine Sample Targets")

endfunction()

add_sample("FalconEngine.Sample.Viewer" "Viewer")